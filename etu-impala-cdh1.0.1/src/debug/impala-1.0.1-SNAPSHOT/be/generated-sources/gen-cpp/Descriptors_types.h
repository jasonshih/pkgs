/**
 * Autogenerated by Thrift Compiler (0.9.0)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Descriptors_TYPES_H
#define Descriptors_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include "Types_types.h"
#include "Exprs_types.h"


namespace impala {

struct TTableType {
  enum type {
    HDFS_TABLE = 0,
    HBASE_TABLE = 1
  };
};

extern const std::map<int, const char*> _TTableType_VALUES_TO_NAMES;

struct THdfsFileFormat {
  enum type {
    TEXT = 0,
    LZO_TEXT = 1,
    RC_FILE = 2,
    SEQUENCE_FILE = 3,
    AVRO = 4,
    PARQUET = 5
  };
};

extern const std::map<int, const char*> _THdfsFileFormat_VALUES_TO_NAMES;

struct THdfsCompression {
  enum type {
    NONE = 0,
    DEFAULT = 1,
    GZIP = 2,
    DEFLATE = 3,
    BZIP2 = 4,
    SNAPPY = 5,
    SNAPPY_BLOCKED = 6,
    LZO = 7
  };
};

extern const std::map<int, const char*> _THdfsCompression_VALUES_TO_NAMES;


class TSlotDescriptor {
 public:

  static const char* ascii_fingerprint; // = "EB3FE8AE124263B4B82968C0919DC0FA";
  static const uint8_t binary_fingerprint[16]; // = {0xEB,0x3F,0xE8,0xAE,0x12,0x42,0x63,0xB4,0xB8,0x29,0x68,0xC0,0x91,0x9D,0xC0,0xFA};

  TSlotDescriptor() : id(0), parent(0), slotType(( ::impala::TPrimitiveType::type)0), columnPos(0), byteOffset(0), nullIndicatorByte(0), nullIndicatorBit(0), slotIdx(0), isMaterialized(0) {
  }

  virtual ~TSlotDescriptor() throw() {}

   ::impala::TSlotId id;
   ::impala::TTupleId parent;
   ::impala::TPrimitiveType::type slotType;
  int32_t columnPos;
  int32_t byteOffset;
  int32_t nullIndicatorByte;
  int32_t nullIndicatorBit;
  int32_t slotIdx;
  bool isMaterialized;

  void __set_id(const  ::impala::TSlotId val) {
    id = val;
  }

  void __set_parent(const  ::impala::TTupleId val) {
    parent = val;
  }

  void __set_slotType(const  ::impala::TPrimitiveType::type val) {
    slotType = val;
  }

  void __set_columnPos(const int32_t val) {
    columnPos = val;
  }

  void __set_byteOffset(const int32_t val) {
    byteOffset = val;
  }

  void __set_nullIndicatorByte(const int32_t val) {
    nullIndicatorByte = val;
  }

  void __set_nullIndicatorBit(const int32_t val) {
    nullIndicatorBit = val;
  }

  void __set_slotIdx(const int32_t val) {
    slotIdx = val;
  }

  void __set_isMaterialized(const bool val) {
    isMaterialized = val;
  }

  bool operator == (const TSlotDescriptor & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(parent == rhs.parent))
      return false;
    if (!(slotType == rhs.slotType))
      return false;
    if (!(columnPos == rhs.columnPos))
      return false;
    if (!(byteOffset == rhs.byteOffset))
      return false;
    if (!(nullIndicatorByte == rhs.nullIndicatorByte))
      return false;
    if (!(nullIndicatorBit == rhs.nullIndicatorBit))
      return false;
    if (!(slotIdx == rhs.slotIdx))
      return false;
    if (!(isMaterialized == rhs.isMaterialized))
      return false;
    return true;
  }
  bool operator != (const TSlotDescriptor &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TSlotDescriptor & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(TSlotDescriptor &a, TSlotDescriptor &b);

typedef struct _THdfsPartition__isset {
  _THdfsPartition__isset() : partitionKeyExprs(false) {}
  bool partitionKeyExprs;
} _THdfsPartition__isset;

class THdfsPartition {
 public:

  static const char* ascii_fingerprint; // = "C5B4E3F9EB060082EAAB73BF13CA4CD6";
  static const uint8_t binary_fingerprint[16]; // = {0xC5,0xB4,0xE3,0xF9,0xEB,0x06,0x00,0x82,0xEA,0xAB,0x73,0xBF,0x13,0xCA,0x4C,0xD6};

  THdfsPartition() : lineDelim(0), fieldDelim(0), collectionDelim(0), mapKeyDelim(0), escapeChar(0), fileFormat((THdfsFileFormat::type)0), blockSize(0), compression((THdfsCompression::type)0) {
  }

  virtual ~THdfsPartition() throw() {}

  int8_t lineDelim;
  int8_t fieldDelim;
  int8_t collectionDelim;
  int8_t mapKeyDelim;
  int8_t escapeChar;
  THdfsFileFormat::type fileFormat;
  std::vector< ::impala::TExpr>  partitionKeyExprs;
  int32_t blockSize;
  THdfsCompression::type compression;

  _THdfsPartition__isset __isset;

  void __set_lineDelim(const int8_t val) {
    lineDelim = val;
  }

  void __set_fieldDelim(const int8_t val) {
    fieldDelim = val;
  }

  void __set_collectionDelim(const int8_t val) {
    collectionDelim = val;
  }

  void __set_mapKeyDelim(const int8_t val) {
    mapKeyDelim = val;
  }

  void __set_escapeChar(const int8_t val) {
    escapeChar = val;
  }

  void __set_fileFormat(const THdfsFileFormat::type val) {
    fileFormat = val;
  }

  void __set_partitionKeyExprs(const std::vector< ::impala::TExpr> & val) {
    partitionKeyExprs = val;
    __isset.partitionKeyExprs = true;
  }

  void __set_blockSize(const int32_t val) {
    blockSize = val;
  }

  void __set_compression(const THdfsCompression::type val) {
    compression = val;
  }

  bool operator == (const THdfsPartition & rhs) const
  {
    if (!(lineDelim == rhs.lineDelim))
      return false;
    if (!(fieldDelim == rhs.fieldDelim))
      return false;
    if (!(collectionDelim == rhs.collectionDelim))
      return false;
    if (!(mapKeyDelim == rhs.mapKeyDelim))
      return false;
    if (!(escapeChar == rhs.escapeChar))
      return false;
    if (!(fileFormat == rhs.fileFormat))
      return false;
    if (!(partitionKeyExprs == rhs.partitionKeyExprs))
      return false;
    if (!(blockSize == rhs.blockSize))
      return false;
    if (!(compression == rhs.compression))
      return false;
    return true;
  }
  bool operator != (const THdfsPartition &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const THdfsPartition & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(THdfsPartition &a, THdfsPartition &b);


class THdfsTable {
 public:

  static const char* ascii_fingerprint; // = "22C74049279DAED9A73D805FEB36B6C3";
  static const uint8_t binary_fingerprint[16]; // = {0x22,0xC7,0x40,0x49,0x27,0x9D,0xAE,0xD9,0xA7,0x3D,0x80,0x5F,0xEB,0x36,0xB6,0xC3};

  THdfsTable() : hdfsBaseDir(), nullPartitionKeyValue(), nullColumnValue() {
  }

  virtual ~THdfsTable() throw() {}

  std::string hdfsBaseDir;
  std::vector<std::string>  colNames;
  std::string nullPartitionKeyValue;
  std::string nullColumnValue;
  std::map<int64_t, THdfsPartition>  partitions;

  void __set_hdfsBaseDir(const std::string& val) {
    hdfsBaseDir = val;
  }

  void __set_colNames(const std::vector<std::string> & val) {
    colNames = val;
  }

  void __set_nullPartitionKeyValue(const std::string& val) {
    nullPartitionKeyValue = val;
  }

  void __set_nullColumnValue(const std::string& val) {
    nullColumnValue = val;
  }

  void __set_partitions(const std::map<int64_t, THdfsPartition> & val) {
    partitions = val;
  }

  bool operator == (const THdfsTable & rhs) const
  {
    if (!(hdfsBaseDir == rhs.hdfsBaseDir))
      return false;
    if (!(colNames == rhs.colNames))
      return false;
    if (!(nullPartitionKeyValue == rhs.nullPartitionKeyValue))
      return false;
    if (!(nullColumnValue == rhs.nullColumnValue))
      return false;
    if (!(partitions == rhs.partitions))
      return false;
    return true;
  }
  bool operator != (const THdfsTable &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const THdfsTable & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(THdfsTable &a, THdfsTable &b);


class THBaseTable {
 public:

  static const char* ascii_fingerprint; // = "16AF767043B70C30A915A930850B1F70";
  static const uint8_t binary_fingerprint[16]; // = {0x16,0xAF,0x76,0x70,0x43,0xB7,0x0C,0x30,0xA9,0x15,0xA9,0x30,0x85,0x0B,0x1F,0x70};

  THBaseTable() : tableName() {
  }

  virtual ~THBaseTable() throw() {}

  std::string tableName;
  std::vector<std::string>  families;
  std::vector<std::string>  qualifiers;

  void __set_tableName(const std::string& val) {
    tableName = val;
  }

  void __set_families(const std::vector<std::string> & val) {
    families = val;
  }

  void __set_qualifiers(const std::vector<std::string> & val) {
    qualifiers = val;
  }

  bool operator == (const THBaseTable & rhs) const
  {
    if (!(tableName == rhs.tableName))
      return false;
    if (!(families == rhs.families))
      return false;
    if (!(qualifiers == rhs.qualifiers))
      return false;
    return true;
  }
  bool operator != (const THBaseTable &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const THBaseTable & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(THBaseTable &a, THBaseTable &b);

typedef struct _TTableDescriptor__isset {
  _TTableDescriptor__isset() : hdfsTable(false), hbaseTable(false) {}
  bool hdfsTable;
  bool hbaseTable;
} _TTableDescriptor__isset;

class TTableDescriptor {
 public:

  static const char* ascii_fingerprint; // = "3BF3017E229F63281F413DC9D08A8AE6";
  static const uint8_t binary_fingerprint[16]; // = {0x3B,0xF3,0x01,0x7E,0x22,0x9F,0x63,0x28,0x1F,0x41,0x3D,0xC9,0xD0,0x8A,0x8A,0xE6};

  TTableDescriptor() : id(0), tableType((TTableType::type)0), numCols(0), numClusteringCols(0), tableName(), dbName() {
  }

  virtual ~TTableDescriptor() throw() {}

   ::impala::TTableId id;
  TTableType::type tableType;
  int32_t numCols;
  int32_t numClusteringCols;
  THdfsTable hdfsTable;
  THBaseTable hbaseTable;
  std::string tableName;
  std::string dbName;

  _TTableDescriptor__isset __isset;

  void __set_id(const  ::impala::TTableId val) {
    id = val;
  }

  void __set_tableType(const TTableType::type val) {
    tableType = val;
  }

  void __set_numCols(const int32_t val) {
    numCols = val;
  }

  void __set_numClusteringCols(const int32_t val) {
    numClusteringCols = val;
  }

  void __set_hdfsTable(const THdfsTable& val) {
    hdfsTable = val;
    __isset.hdfsTable = true;
  }

  void __set_hbaseTable(const THBaseTable& val) {
    hbaseTable = val;
    __isset.hbaseTable = true;
  }

  void __set_tableName(const std::string& val) {
    tableName = val;
  }

  void __set_dbName(const std::string& val) {
    dbName = val;
  }

  bool operator == (const TTableDescriptor & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(tableType == rhs.tableType))
      return false;
    if (!(numCols == rhs.numCols))
      return false;
    if (!(numClusteringCols == rhs.numClusteringCols))
      return false;
    if (__isset.hdfsTable != rhs.__isset.hdfsTable)
      return false;
    else if (__isset.hdfsTable && !(hdfsTable == rhs.hdfsTable))
      return false;
    if (__isset.hbaseTable != rhs.__isset.hbaseTable)
      return false;
    else if (__isset.hbaseTable && !(hbaseTable == rhs.hbaseTable))
      return false;
    if (!(tableName == rhs.tableName))
      return false;
    if (!(dbName == rhs.dbName))
      return false;
    return true;
  }
  bool operator != (const TTableDescriptor &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TTableDescriptor & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(TTableDescriptor &a, TTableDescriptor &b);

typedef struct _TTupleDescriptor__isset {
  _TTupleDescriptor__isset() : tableId(false) {}
  bool tableId;
} _TTupleDescriptor__isset;

class TTupleDescriptor {
 public:

  static const char* ascii_fingerprint; // = "10850C26C1AD0C180808B8FC6F756B91";
  static const uint8_t binary_fingerprint[16]; // = {0x10,0x85,0x0C,0x26,0xC1,0xAD,0x0C,0x18,0x08,0x08,0xB8,0xFC,0x6F,0x75,0x6B,0x91};

  TTupleDescriptor() : id(0), byteSize(0), numNullBytes(0), tableId(0) {
  }

  virtual ~TTupleDescriptor() throw() {}

   ::impala::TTupleId id;
  int32_t byteSize;
  int32_t numNullBytes;
   ::impala::TTableId tableId;

  _TTupleDescriptor__isset __isset;

  void __set_id(const  ::impala::TTupleId val) {
    id = val;
  }

  void __set_byteSize(const int32_t val) {
    byteSize = val;
  }

  void __set_numNullBytes(const int32_t val) {
    numNullBytes = val;
  }

  void __set_tableId(const  ::impala::TTableId val) {
    tableId = val;
    __isset.tableId = true;
  }

  bool operator == (const TTupleDescriptor & rhs) const
  {
    if (!(id == rhs.id))
      return false;
    if (!(byteSize == rhs.byteSize))
      return false;
    if (!(numNullBytes == rhs.numNullBytes))
      return false;
    if (__isset.tableId != rhs.__isset.tableId)
      return false;
    else if (__isset.tableId && !(tableId == rhs.tableId))
      return false;
    return true;
  }
  bool operator != (const TTupleDescriptor &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TTupleDescriptor & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(TTupleDescriptor &a, TTupleDescriptor &b);

typedef struct _TDescriptorTable__isset {
  _TDescriptorTable__isset() : slotDescriptors(false), tableDescriptors(false) {}
  bool slotDescriptors;
  bool tableDescriptors;
} _TDescriptorTable__isset;

class TDescriptorTable {
 public:

  static const char* ascii_fingerprint; // = "54EFE7ED1B60E4AEC21C6510DC01C166";
  static const uint8_t binary_fingerprint[16]; // = {0x54,0xEF,0xE7,0xED,0x1B,0x60,0xE4,0xAE,0xC2,0x1C,0x65,0x10,0xDC,0x01,0xC1,0x66};

  TDescriptorTable() {
  }

  virtual ~TDescriptorTable() throw() {}

  std::vector<TSlotDescriptor>  slotDescriptors;
  std::vector<TTupleDescriptor>  tupleDescriptors;
  std::vector<TTableDescriptor>  tableDescriptors;

  _TDescriptorTable__isset __isset;

  void __set_slotDescriptors(const std::vector<TSlotDescriptor> & val) {
    slotDescriptors = val;
    __isset.slotDescriptors = true;
  }

  void __set_tupleDescriptors(const std::vector<TTupleDescriptor> & val) {
    tupleDescriptors = val;
  }

  void __set_tableDescriptors(const std::vector<TTableDescriptor> & val) {
    tableDescriptors = val;
    __isset.tableDescriptors = true;
  }

  bool operator == (const TDescriptorTable & rhs) const
  {
    if (__isset.slotDescriptors != rhs.__isset.slotDescriptors)
      return false;
    else if (__isset.slotDescriptors && !(slotDescriptors == rhs.slotDescriptors))
      return false;
    if (!(tupleDescriptors == rhs.tupleDescriptors))
      return false;
    if (__isset.tableDescriptors != rhs.__isset.tableDescriptors)
      return false;
    else if (__isset.tableDescriptors && !(tableDescriptors == rhs.tableDescriptors))
      return false;
    return true;
  }
  bool operator != (const TDescriptorTable &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TDescriptorTable & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(TDescriptorTable &a, TDescriptorTable &b);

} // namespace

#endif