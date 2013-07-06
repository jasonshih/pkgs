// Copyright 2012 Cloudera Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "exec/hdfs-parquet-scanner.h"

#include "common/object-pool.h"
#include "exec/hdfs-scan-node.h"
#include "exec/scanner-context.inline.h"
#include "exec/read-write-util.h"
#include "exprs/expr.h"
#include "runtime/descriptors.h"
#include "runtime/runtime-state.h"
#include "runtime/mem-pool.h"
#include "runtime/raw-value.h"
#include "runtime/row-batch.h"
#include "runtime/tuple-row.h"
#include "runtime/tuple.h"
#include "runtime/string-value.h"
#include "util/bit-util.h"
#include "util/decompress.h"
#include "util/debug-util.h"
#include "util/rle-encoding.h"
#include "util/runtime-profile.h"
#include "util/thrift-util.h"

using namespace std;
using namespace boost;
using namespace impala;

// Issue just the footer range for each file.  We'll then parse the footer and pick out
// the columns we want.
void HdfsParquetScanner::IssueInitialRanges(HdfsScanNode* scan_node,
    const std::vector<HdfsFileDesc*>& files) {
  for (int i = 0; i < files.size(); ++i) {
    for (int j = 0; j < files[i]->splits.size(); ++j) {
      DiskIoMgr::ScanRange* split = files[i]->splits[j];

      // Since Parquet scanners always read entire files, only read a file if we're
      // assigned the first split to avoid reading multi-block files with multiple
      // scanners.
      if (split->offset() != 0) {
        // We are expecting each file to be one hdfs block (so all the scan range offsets
        // should be 0).  This is not incorrect but we will issue a warning.
        LOG(WARNING) << "Parquet file should not be split into multiple hdfs-blocks."
                     << " file=" << files[i]->filename;
        // We assign the entire file to one scan range, so mark all but one split
        // (i.e. the first split) as complete
        scan_node->RangeComplete(THdfsFileFormat::PARQUET, THdfsCompression::NONE);
        continue;
      }

      // Compute the offset of the file footer
      DCHECK_GT(files[i]->file_length, 0);
      int64_t footer_start = max(0L, files[i]->file_length - FOOTER_SIZE);

      ScanRangeMetadata* metadata =
          reinterpret_cast<ScanRangeMetadata*>(files[i]->splits[0]->meta_data());
      DiskIoMgr::ScanRange* footer_range = scan_node->AllocateScanRange(
          files[i]->filename.c_str(), FOOTER_SIZE,
          footer_start, metadata->partition_id, files[i]->splits[0]->disk_id());
      scan_node->AddDiskIoRange(footer_range);
    }
  }
}

HdfsParquetScanner::HdfsParquetScanner(HdfsScanNode* scan_node, RuntimeState* state) 
    : HdfsScanner(scan_node, state),
      metadata_range_(NULL),
      assemble_rows_timer_(scan_node_->materialize_tuple_timer()) {
  assemble_rows_timer_.Stop();
}

HdfsParquetScanner::~HdfsParquetScanner() {
}

// Reader for a single column from the parquet file.  It's associated with a 
// ScannerContext::Stream and is responsible for decoding the data.
class HdfsParquetScanner::ColumnReader {
 public:
  ColumnReader(HdfsParquetScanner* parent, const SlotDescriptor* desc) 
    : parent_(parent),
      desc_(desc),
      field_repetition_type_(parquet::FieldRepetitionType::OPTIONAL),
      decompressed_data_pool_(
          new MemPool(parent->scan_node_->runtime_state()->mem_limits())),
      num_buffered_values_(0) {
  }

  Status Reset(const parquet::SchemaElement* schema_element,
      const parquet::ColumnMetaData* metadata, ScannerContext::Stream* stream) {
    DCHECK(stream != NULL);
    DCHECK(metadata != NULL);

    field_repetition_type_ = schema_element->repetition_type;
    num_buffered_values_ = 0;
    data_ = NULL;
    stream_ = stream;
    metadata_ = metadata; 
    if (metadata_->codec != parquet::CompressionCodec::UNCOMPRESSED) {
      RETURN_IF_ERROR(Codec::CreateDecompressor(
          parent_->scan_node_->runtime_state(), NULL, false,
          PARQUET_TO_IMPALA_CODEC[metadata_->codec], &decompressor_));
    }
    return Status::OK;
  }

  int64_t total_len() const { return metadata_->total_compressed_size; }
  const SlotDescriptor* slot_desc() const { return desc_; }

  // Read the next value into tuple for this column.  Returns 
  // false if there are no more values in the file.
  // TODO: this is the function that needs to be codegen'd (e.g. CodegenReadValue())
  // The codegened functions from all the materialized cols will then be combined
  // into one function.
  // TODO: another option is to materialize col by col for the entire row batch in
  // one call.  e.g. MaterializeCol would write out 1024 values.  Our row batches
  // are currently dense so we'll need to figure out something there.
  bool ReadValue(MemPool* pool, Tuple* tuple);

 private:
  friend class HdfsParquetScanner;

  HdfsParquetScanner* parent_;
  const SlotDescriptor* desc_;

  // This is either required, optional or repeated.
  // If it is required, the column cannot have NULLs.
  parquet::FieldRepetitionType::type field_repetition_type_;

  const parquet::ColumnMetaData* metadata_;
  scoped_ptr<Codec> decompressor_;
  ScannerContext::Stream* stream_;

  // Pool to allocate decompression buffers from.
  boost::scoped_ptr<MemPool> decompressed_data_pool_;

  // Header for current data page.
  parquet::PageHeader current_page_header_;

  // Num values remaining in the current data page
  int num_buffered_values_;

  // Pointer to start of next value in data page
  uint8_t* data_;

  // Decoder for bool values.  Only valid if type is TYPE_BOOLEAN
  BitReader bool_values_;

  // Decoder for definition.  Only one of these is valid at a time, depending on
  // the data page metadata.
  RleDecoder rle_def_levels_;
  BitReader bit_packed_def_levels_;

  // Read the next data page.
  Status ReadDataPage();

  // Returns the definition level for the next value
  // Returns -1 if there was a error parsing it.
  int ReadDefinitionLevel();
};

Status HdfsParquetScanner::Prepare() {
  RETURN_IF_ERROR(HdfsScanner::Prepare());
  column_readers_.resize(scan_node_->materialized_slots().size());
  for (int i = 0; i < scan_node_->materialized_slots().size(); ++i) {
    column_readers_[i] = scan_node_->runtime_state()->obj_pool()->Add(
        new ColumnReader(this, scan_node_->materialized_slots()[i]));
  }
  
  decompress_timer_ = ADD_TIMER(scan_node_->runtime_profile(), "DecompressionTime");
  num_cols_counter_ = 
      ADD_COUNTER(scan_node_->runtime_profile(), "NumColumns", TCounterType::UNIT);

  scan_node_->IncNumScannersCodegenDisabled();
  return Status::OK;
}

Status HdfsParquetScanner::Close() {
  context_->Close();
  // TODO: this doesn't really work for parquet since the file is 
  // not uniformly compressed.
  scan_node_->RangeComplete(THdfsFileFormat::PARQUET, THdfsCompression::NONE);
  assemble_rows_timer_.UpdateCounter();
  return Status::OK;
}

Status HdfsParquetScanner::ColumnReader::ReadDataPage() {
  Status status;
  
  uint8_t* buffer;
  int num_bytes;
  bool eos;

  // We're about to move to the next data page.  The previous data page is 
  // now complete, pass along the memory allocated for it.
  parent_->context_->AcquirePool(decompressed_data_pool_.get());

  // Read the next data page, skipping page types we don't care about.
  // We break out of this loop on the non-error case (either eosr or
  // a data page was found).
  while (true) {
    DCHECK_EQ(num_buffered_values_, 0);
    RETURN_IF_ERROR(stream_->GetRawBytes(&buffer, &num_bytes, &eos));
    if (num_bytes == 0) {
      DCHECK(eos);
      break;
    }

    // We don't know the actual header size until the thrift object is deserialized.
    uint32_t header_size = num_bytes;
    status = DeserializeThriftMsg(buffer, &header_size, true, &current_page_header_);
    if (!status.ok()) {
      if (header_size >= MAX_PAGE_HEADER_SIZE) {
        status.AddErrorMsg("ParquetScanner: Could not deserialize page header.");
        return status;
      }
      // Stitch the header bytes that are split across buffers.
      uint8_t header_buffer[MAX_PAGE_HEADER_SIZE];
      int header_first_part = header_size;
      memcpy(header_buffer, buffer, header_first_part);
     
      if (!stream_->SkipBytes(header_first_part, &status)) return status;
      RETURN_IF_ERROR(stream_->GetRawBytes(&buffer, &num_bytes, &eos));
      if (num_bytes == 0) return status;

      uint32_t header_second_part = 
          ::min(num_bytes, MAX_PAGE_HEADER_SIZE - header_first_part);
      memcpy(header_buffer + header_first_part, buffer, header_second_part);
      header_size = MAX_PAGE_HEADER_SIZE;
      status = 
          DeserializeThriftMsg(header_buffer, &header_size, true, &current_page_header_);

      if (!status.ok()) {
        status.AddErrorMsg("ParquetScanner: Could not deserialize page header.");
        return status;
      }
      DCHECK_GT(header_size, header_first_part);
      header_size = header_size - header_first_part;
    }
    if (!stream_->SkipBytes(header_size, &status)) return status;

    int data_size = current_page_header_.compressed_page_size;
    if (current_page_header_.type != parquet::PageType::DATA_PAGE) {
      // We can safely skip non-data pages
      if (!stream_->SkipBytes(data_size, &status)) return status;
      continue;
    }

    if (!stream_->ReadBytes(data_size, &data_, &status)) return status;

    num_buffered_values_ = current_page_header_.data_page_header.num_values;

    int uncompressed_size = current_page_header_.uncompressed_page_size;
    if (decompressor_.get() != NULL) {
      SCOPED_TIMER(parent_->decompress_timer_);
      uint8_t* decompressed_buffer = decompressed_data_pool_->Allocate(uncompressed_size);
      RETURN_IF_ERROR(decompressor_->ProcessBlock(
          current_page_header_.compressed_page_size, data_, 
          &uncompressed_size, &decompressed_buffer)); 
      DCHECK_EQ(current_page_header_.uncompressed_page_size, uncompressed_size);
      data_ = decompressed_buffer;
      data_size = current_page_header_.uncompressed_page_size;
    } else {
      DCHECK_EQ(metadata_->codec, parquet::CompressionCodec::UNCOMPRESSED);
      DCHECK_EQ(current_page_header_.compressed_page_size, uncompressed_size);
    }

    if (field_repetition_type_ == parquet::FieldRepetitionType::OPTIONAL) {
      // Initialize the definition level data
      int32_t num_definition_bytes = 0;
      switch (current_page_header_.data_page_header.definition_level_encoding) {
        case parquet::Encoding::RLE:
          if (!ReadWriteUtil::Read(&data_, &data_size, &num_definition_bytes, &status)) {
            return status;
          }
          rle_def_levels_ = RleDecoder(data_, num_definition_bytes);
          break;
        case parquet::Encoding::BIT_PACKED:
          num_definition_bytes = BitUtil::Ceil(num_buffered_values_, 8);
          bit_packed_def_levels_ = BitReader(data_, num_definition_bytes);
          break;
        default: {
          stringstream ss;
          ss << "Unsupported definition level encoding: " 
            << current_page_header_.data_page_header.definition_level_encoding;
          return Status(ss.str());
        }
      }
      DCHECK_GT(num_definition_bytes, 0);
      data_ += num_definition_bytes;
      data_size -= num_definition_bytes;
    }

    if (desc_->type() == TYPE_BOOLEAN) {
      // Initialize bool decoder
      bool_values_ = BitReader(data_, data_size);
    }

    break;
  }
    
  return Status::OK;
}
  
// TODO More codegen here as well.
inline int HdfsParquetScanner::ColumnReader::ReadDefinitionLevel() {
  if (field_repetition_type_ == parquet::FieldRepetitionType::REQUIRED) {
    // This column is required so there is nothing encoded for the definition
    // levels.
    return 1;
  }

  uint8_t definition_level;
  bool valid;
  switch (current_page_header_.data_page_header.definition_level_encoding) {
    case parquet::Encoding::RLE:
      valid = rle_def_levels_.Get(&definition_level);
      break;
    case parquet::Encoding::BIT_PACKED: {
      bool v;
      valid = bit_packed_def_levels_.GetBool(&v);
      definition_level = v;
      break;
    }
    default:
      DCHECK(false);
  }
  if (!valid) return -1;
  return definition_level;
}
  
inline bool HdfsParquetScanner::ColumnReader::ReadValue(MemPool* pool, Tuple* tuple) {
  if (num_buffered_values_ == 0) {
    parent_->assemble_rows_timer_.Stop();
    parent_->parse_status_ = ReadDataPage();
    if (num_buffered_values_ == 0) return false;
    parent_->assemble_rows_timer_.Start();
  }
  
  --num_buffered_values_;
  int definition_level = ReadDefinitionLevel();
  if (definition_level < 0) return false;

  if (definition_level == 0) {
    // Null value
    tuple->SetNull(desc_->null_indicator_offset());
    return true;
  }

  DCHECK_EQ(definition_level, 1);

  void* slot = tuple->GetSlot(desc_->tuple_offset());
  switch (desc_->type()) {
    case TYPE_BOOLEAN: {
      bool valid;
      valid = bool_values_.GetBool(reinterpret_cast<bool*>(slot));
      if (!valid) {
        parent_->parse_status_ = Status("Invalid bool column");
        return false;
      }
      break;
    }
    case TYPE_TINYINT:
      *reinterpret_cast<int8_t*>(slot) = *reinterpret_cast<int32_t*>(data_);
      data_ += 4;
      break;
    case TYPE_SMALLINT:
      *reinterpret_cast<int16_t*>(slot) = *reinterpret_cast<int32_t*>(data_);
      data_ += 4;
      break;
    case TYPE_INT:
      *reinterpret_cast<int32_t*>(slot) = *reinterpret_cast<int32_t*>(data_);
      data_ += 4;
      break;
    case TYPE_BIGINT:
      *reinterpret_cast<int64_t*>(slot) = *reinterpret_cast<int64_t*>(data_);
      data_ += 8;
      break;
    case TYPE_FLOAT:
      *reinterpret_cast<float*>(slot) = *reinterpret_cast<float*>(data_);
      data_ += 4;
      break;
    case TYPE_DOUBLE:
      *reinterpret_cast<double*>(slot) = *reinterpret_cast<double*>(data_);
      data_ += 8;
      break;
    case TYPE_STRING: {
      StringValue* sv = reinterpret_cast<StringValue*>(slot);
      sv->len = *reinterpret_cast<int32_t*>(data_);
      data_ += sizeof(int32_t);
      if (stream_->compact_data() && sv->len > 0) {
        sv->ptr = reinterpret_cast<char*>(pool->Allocate(sv->len));
        memcpy(sv->ptr, data_, sv->len);
      } else {
        sv->ptr = reinterpret_cast<char*>(data_);
      }
      data_ += sv->len;
      break;
    }
    case TYPE_TIMESTAMP: 
      // timestamp type is a 12 byte value.
      memcpy(slot, data_, 12);
      data_ += 12;
      break;
    default:
      DCHECK(false);
  }
  return true;
}
  
Status HdfsParquetScanner::ProcessSplit(ScannerContext* context) {
  SetContext(context);

  HdfsFileDesc* file_desc = scan_node_->GetFileDesc(stream_->filename());
  DCHECK(file_desc != NULL);
  
  // First process the file metadata in the footer
  bool eosr;
  RETURN_IF_ERROR(ProcessFooter(&eosr));

  if (eosr) return Status::OK;
    
  // We've processed the metadata and there are columns that need to be
  // materialized.
  COUNTER_SET(num_cols_counter_, static_cast<int64_t>(column_readers_.size()));
  
  // Iterate through each row group in the file and read all the materialized columns
  // per row group.  Row groups are independent, so this this could be parallelized.
  // However, having multiple row groups per file should be seen as an edge case and
  // we can do better parallelizing across files instead.
  for (int i = 0; i < file_metadata_.row_groups.size(); ++i) {
    // Release the token that was used to process the previous range(s).  This thread
    // will be reused to assemble the cols for this row group.
    scan_node_->runtime_state()->resource_pool()->ReleaseThreadToken(false);

    // Tell the context the number of streams (aka cols) there will be and initialize
    // column_readers_ to the correct stream objects
    context_->CreateStreams(scan_node_->materialized_slots().size());

    // TODO: better error handling
    RETURN_IF_ERROR(InitColumns(i));
    RETURN_IF_ERROR(AssembleRows());
  }

  return Status::OK;
}

// TODO: this needs to be codegen'd.  The ReadValue function needs to be codegen'd,
// specific to type and encoding and then inlined into AssembleRows().
Status HdfsParquetScanner::AssembleRows() {
  assemble_rows_timer_.Start();
  while (!scan_node_->ReachedLimit() && !context_->cancelled()) {
    MemPool* pool;
    Tuple* tuple;
    TupleRow* row;
    int num_rows = context_->GetMemory(&pool, &tuple, &row);
    int num_to_commit = 0;

    for (int i = 0; i < num_rows; ++i) {
      InitTuple(context_->template_tuple(), tuple);
      for (int c = 0; c < column_readers_.size(); ++c) {
        if (!column_readers_[c]->ReadValue(pool, tuple)) {
          assemble_rows_timer_.Stop();
          // This column is complete and has no more data.  This indicates
          // we are done with this row group.
          // For correctly formed files, this should be the first column we
          // are reading.
          DCHECK(c == 0 || !parse_status_.ok()) << "c=" << c << " " 
              << parse_status_.GetErrorMsg();;
          context_->CommitRows(num_to_commit);
          COUNTER_UPDATE(scan_node_->rows_read_counter(), i);
          return parse_status_;
        }
      }
    
      row->SetTuple(scan_node_->tuple_idx(), tuple);
      if (ExecNode::EvalConjuncts(conjuncts_, num_conjuncts_, row)) {
        row = context_->next_row(row);
        tuple = context_->next_tuple(tuple);
        ++num_to_commit;
      } 
    }
    context_->CommitRows(num_to_commit);
    COUNTER_UPDATE(scan_node_->rows_read_counter(), num_rows);
  }

  assemble_rows_timer_.Stop();
  if (context_->cancelled()) return Status::CANCELLED;
  return parse_status_;
}

Status HdfsParquetScanner::ProcessFooter(bool* eosr) {
  *eosr = false;

  // Need to loop in case we need to read more bytes.
  while (true) {
    uint8_t* buffer;
    int len;
    bool eos;

    if (!stream_->GetBytes(0, &buffer, &len, &eos, &parse_status_)) {
      return parse_status_;
    }
    DCHECK(eos);

    // Number of bytes in buffer after the fixed size footer is accounted for.
    int remaining_bytes_buffered = len - sizeof(int32_t) - sizeof(PARQUET_VERSION_NUMBER);

    // Make sure footer has enough bytes to contain the required information.
    if (remaining_bytes_buffered < 0) {
      stringstream ss;
      ss << "File " << stream_->filename() << " is invalid.  Missing metadata.";
      return Status(ss.str());
    }

    // Validate magic file bytes are correct
    uint8_t* magic_number_ptr = buffer + len - sizeof(PARQUET_VERSION_NUMBER);
    if (memcmp(magic_number_ptr, 
        PARQUET_VERSION_NUMBER, sizeof(PARQUET_VERSION_NUMBER) != 0)) {
      stringstream ss;
      ss << "File " << stream_->filename() << " is invalid.  Invalid file footer: "
         << string((char*)magic_number_ptr, sizeof(PARQUET_VERSION_NUMBER));
      return Status(ss.str());
    }

    // The size of the metadata is encoded as a 4 byte little endian value before
    // the magic number
    uint8_t* metadata_size_ptr = magic_number_ptr - sizeof(int32_t);
    uint32_t metadata_size = *reinterpret_cast<uint32_t*>(metadata_size_ptr);

    // TODO: we need to read more from the file, the footer size guess was wrong.
    DCHECK_LE(metadata_size, remaining_bytes_buffered);

    // Deserialize file header
    uint8_t* metadata_ptr = metadata_size_ptr - metadata_size;
    Status status = 
        DeserializeThriftMsg(metadata_ptr, &metadata_size, true, &file_metadata_);
    if (!status.ok()) {
      stringstream ss;
      ss << "File " << stream_->filename() << " has invalid file metadata at file offset "
         << (metadata_size + sizeof(PARQUET_VERSION_NUMBER) + sizeof(uint32_t)) << ". "
         << "Error = " << status.GetErrorMsg();
      return Status(ss.str());
    }

    metadata_range_ = stream_->scan_range();
    RETURN_IF_ERROR(ValidateFileMetadata());

    if (scan_node_->materialized_slots().empty()) {
      // No materialized columns.  We can serve this query from just the metadata.  We
      // don't need to read the column data.
      int64_t num_tuples = file_metadata_.num_rows;
      COUNTER_UPDATE(scan_node_->rows_read_counter(), num_tuples);

      while (num_tuples > 0) {
        MemPool* pool;
        Tuple* tuple;
        TupleRow* current_row;
        int max_tuples = context_->GetMemory(&pool, &tuple, &current_row);
        max_tuples = min(static_cast<int64_t>(max_tuples), num_tuples);
        num_tuples -= max_tuples;

        int num_to_commit = WriteEmptyTuples(context_, current_row, max_tuples);
        if (num_to_commit > 0) context_->CommitRows(num_to_commit);
      }

      *eosr = true;
      return Status::OK;
    }
    
    if (file_metadata_.row_groups.empty()) {
      stringstream ss;
      ss << "Invalid file. This file: " << stream_->filename() << " has no row groups";
      return Status(ss.str());
    }
    break;
  }
  return Status::OK;
}

Status HdfsParquetScanner::InitColumns(int row_group_idx) {
  int num_partition_keys = scan_node_->num_partition_keys();
  parquet::RowGroup& row_group = file_metadata_.row_groups[row_group_idx];

  DiskIoMgr::ScanRangeGroup* scan_range_group = 
      scan_node_->runtime_state()->obj_pool()->Add(new DiskIoMgr::ScanRangeGroup);

  // Walk over the materialized columns
  for (int i = 0; i < scan_node_->materialized_slots().size(); ++i) {
    int col_idx = scan_node_->materialized_slots()[i]->col_pos() - num_partition_keys;
    if (col_idx >= row_group.columns.size()) {
      stringstream ss;
      ss << "File " << stream_->filename() << ": metadata is incompatible "
         << "with the schema.  Schema expects " << (col_idx + 1) << " cols, while the "
         << "file only has " << (row_group.columns.size() + 1) << " cols.";
      return Status(ss.str());
    }

    RETURN_IF_ERROR(ValidateColumn(i, col_idx));

    const parquet::SchemaElement& schema_element = file_metadata_.schema[col_idx + 1];
    const parquet::ColumnChunk& col_chunk = row_group.columns[col_idx];
    int64_t col_start = col_chunk.meta_data.data_page_offset;
    int64_t col_len = col_chunk.meta_data.total_compressed_size;

    // TODO: this will need to change when we have co-located files and the columns
    // are different files.
    if (!col_chunk.file_path.empty()) {
      DCHECK_EQ(col_chunk.file_path, string(metadata_range_->file()));
    }

    // Get the stream that will be used for this column
    ScannerContext::Stream* stream = context_->GetStream(i);
    DCHECK(stream != NULL);
    RETURN_IF_ERROR(column_readers_[i]->Reset(&schema_element, 
        &col_chunk.meta_data, stream));

    if (scan_node_->materialized_slots()[i]->type() != TYPE_STRING ||
        col_chunk.meta_data.codec != parquet::CompressionCodec::UNCOMPRESSED) {
      // Non-string types are always compact.  Compressed columns don't reference data
      // in the io buffers after tuple materialization.  In both cases, we can set compact
      // to true and recycle buffers more promptly.
      stream->set_compact_data(true);
    }

    DiskIoMgr::ScanRange* col_range = scan_node_->AllocateScanRange(
        metadata_range_->file(), col_len, col_start, i, metadata_range_->disk_id(),
        stream);
    scan_range_group->ranges.push_back(col_range);
  }
  DCHECK_EQ(scan_node_->materialized_slots().size(), scan_range_group->ranges.size());
  DCHECK_EQ(scan_node_->materialized_slots().size(), column_readers_.size());

  // The super class stream is not longer valid/used.  It was used
  // just to parse the file header.
  stream_ = NULL;  

  // Issue all the column chunks to the io mgr.
  vector<DiskIoMgr::ScanRangeGroup*> groups;
  groups.push_back(scan_range_group);
  RETURN_IF_ERROR(scan_node_->runtime_state()->io_mgr()->AddScanRangeGroups(
      scan_node_->reader_context(), groups));

  return Status::OK;
}

Status HdfsParquetScanner::ValidateFileMetadata() {
  if (file_metadata_.version > PARQUET_CURRENT_VERSION) {
    stringstream ss;
    ss << "File: " << stream_->filename() << " is of an unsupported version. "
       << "file version: " << file_metadata_.version;
    return Status(ss.str());
  } 
  return Status::OK;
}

bool IsEncodingSupported(parquet::Encoding::type e) {
  switch (e) {
    case parquet::Encoding::PLAIN:
    case parquet::Encoding::BIT_PACKED:
    case parquet::Encoding::RLE:
      return true;
    default:
      return false;
  }
}

Status HdfsParquetScanner::ValidateColumn(int slot_idx, int col_idx) {
  parquet::ColumnChunk& file_data = file_metadata_.row_groups[0].columns[col_idx];
  const parquet::SchemaElement& schema_element = file_metadata_.schema[col_idx + 1];

  // Check the encodings are supported
  vector<parquet::Encoding::type>& encodings = file_data.meta_data.encodings;
  for (int i = 0; i < encodings.size(); ++i) {
    if (!IsEncodingSupported(encodings[i])) {
      stringstream ss;
      ss << "File " << stream_->filename() << " uses an unsupported encoding: " 
         << PrintEncoding(encodings[i]) << " for column " << schema_element.name;
      return Status(ss.str());
    }
  }

  // Check the compression is supported
  if (file_data.meta_data.codec != parquet::CompressionCodec::UNCOMPRESSED &&
      file_data.meta_data.codec != parquet::CompressionCodec::SNAPPY &&
      file_data.meta_data.codec != parquet::CompressionCodec::GZIP) {
    stringstream ss;
    ss << "File " << stream_->filename() << " uses an unsupported compression: " 
        << file_data.meta_data.codec << " for column " << schema_element.name;
    return Status(ss.str());
  }

  // Check the type in the file is compatible with the catalog metadata.
  ColumnReader* impala_data = column_readers_[slot_idx];
  parquet::Type::type type = IMPALA_TO_PARQUET_TYPES[impala_data->desc_->type()];
  if (type != file_data.meta_data.type) {
    stringstream ss;
    ss << "File " << stream_->filename() << " has an incompatible type with the"
       << " table schema for column " << schema_element.name << ".  Expected type: "
       << type << ".  Actual type: " << file_data.meta_data.type;
    return Status(ss.str());
  }

  // Check that the column is not nested
  const vector<string> schema_path = file_data.meta_data.path_in_schema;
  if (schema_path.size() != 1) {
    stringstream ss;
    ss << "File " << stream_->filename() << " contains a nested schema for column "
       << schema_element.name << ".  This is currently not supported.";
    return Status(ss.str());
  }

  // Check that this column is optional or required
  if (schema_element.repetition_type != parquet::FieldRepetitionType::OPTIONAL &&
      schema_element.repetition_type != parquet::FieldRepetitionType::REQUIRED) {
    stringstream ss;
    ss << "File " << stream_->filename() << " column " << schema_element.name 
       << " contains an unsupported column repetition type: " 
       << schema_element.repetition_type;
    return Status(ss.str());
  }

  return Status::OK;
}

