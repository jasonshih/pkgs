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


#ifndef IMPALA_RUNTIME_MEM_POOL_H
#define IMPALA_RUNTIME_MEM_POOL_H

#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string>

#include "common/logging.h"

namespace impala {

class MemLimit;

// A MemPool maintains a list of memory chunks from which it allocates memory in
// response to Allocate() calls;
// Chunks stay around for the lifetime of the mempool or until they are passed on to
// another mempool.
//
// The caller can register a set of MemLimits with the pool, in which case chunk
// allocations are counted against those limits. If chunks get moved between pools
// during AcquireData() calls, the respective MemLimits are updated accordingly.
// Chunks freed up in the d'tor are subtracted from the registered limits.
//
// An Allocate() call will attempt to allocate memory from the chunk that was most
// recently added; if that chunk doesn't have enough memory to
// satisfy the allocation request, the free chunks are searched for one that is
// big enough otherwise a new chunk is added to the list.
// The current_chunk_idx_ always points to the last chunk with allocated memory.
// In order to keep allocation overhead low, chunk sizes double with each new one
// added, until they hit a maximum size.
//
//     Example:
//     MemPool* p = new MemPool();
//     for (int i = 0; i < 1024; ++i) {
// returns 8-byte aligned memory (effectively 24 bytes):
//       .. = p->Allocate(17);
//     }
// at this point, 17K have been handed out in response to Allocate() calls and
// 28K of chunks have been allocated (chunk sizes: 4K, 8K, 16K)
// We track total and peak allocated bytes. At this point they would be the same:
// 28k bytes.  A call to Clear will return the allocated memory so
// total_allocate_bytes_
// becomes 0 while peak_allocate_bytes_ remains at 28k.
//     p->Clear();
// the entire 1st chunk is returned:
//     .. = p->Allocate(4 * 1024);
// 4K of the 2nd chunk are returned:
//     .. = p->Allocate(4 * 1024);
// a new 20K chunk is created
//     .. = p->Allocate(20 * 1024);
//
//      MemPool* p2 = new MemPool();
// the new mempool receives all chunks containing data from p
//      p2->AcquireData(p, false);
// At this point p.total_allocated_bytes_ would be 0 while p.peak_allocated_bytes_ 
// remains unchanged. 
// The one remaining (empty) chunk is released:
//    delete p;

class MemPool {
 public:
  // Allocates mempool with fixed-size chunks of size 'chunk_size'.
  // Chunk_size must be >= 0; 0 requests automatic doubling of chunk sizes,
  // up to a limit.
  // 'limits' are the memlimits for this pool.  NULL can be passed if
  // the mempool should not update limits or if the limits can only
  // be set later.
  MemPool(const std::vector<MemLimit*>* limits, int chunk_size = 0);

  // Frees all chunks of memory and subtracts the total allocated bytes
  // from the registered limits.
  ~MemPool();

  // Allocates 8-byte aligned section of memory of 'size' bytes at the end
  // of the the current chunk. Creates a new chunk if there aren't any chunks
  // with enough capacity.
  uint8_t* Allocate(int size) {
    if (size == 0) return NULL;

    int num_bytes = ((size + 7) / 8) * 8;  // round up to nearest 8 bytes
    if (current_chunk_idx_ == -1
        || num_bytes + chunks_[current_chunk_idx_].allocated_bytes
          > chunks_[current_chunk_idx_].size) {
      FindChunk(num_bytes);
    }
    ChunkInfo& info = chunks_[current_chunk_idx_];
    DCHECK(info.owns_data);
    uint8_t* result = info.data + info.allocated_bytes;
    DCHECK_LE(info.allocated_bytes + num_bytes, info.size);
    info.allocated_bytes += num_bytes;
    total_allocated_bytes_ += num_bytes;
    DCHECK_LE(current_chunk_idx_, chunks_.size() - 1);
    peak_allocated_bytes_ = std::max(total_allocated_bytes_, peak_allocated_bytes_);
    return result;
  }

  // Makes all allocated chunks available for re-use, but doesn't delete any chunks.
  void Clear() {
    current_chunk_idx_ = -1;
    for (std::vector<ChunkInfo>::iterator chunk = chunks_.begin();
         chunk != chunks_.end(); ++chunk) {
      chunk->cumulative_allocated_bytes = 0;
      chunk->allocated_bytes = 0;
    }
    total_allocated_bytes_ = 0;
    DCHECK(CheckIntegrity(false));
  }

  // Absorb all chunks that hold data from src. If keep_current is true, let src hold on
  // to its last allocated chunk that contains data.
  // All offsets handed out by calls to GetOffset()/GetCurrentOffset() for 'src'
  // become invalid.
  void AcquireData(MemPool* src, bool keep_current);

  // Diagnostic to check if memory is allocated from this mempool.
  // Inputs:
  //   ptr: start of memory block.
  //   size: size of memory block.
  // Returns true if memory block is in one of the chunks in this mempool.
  bool Contains(uint8_t* ptr, int size);

  std::string DebugString();

  int64_t total_allocated_bytes() const { return total_allocated_bytes_; }
  int64_t peak_allocated_bytes() const { return peak_allocated_bytes_; }
  const std::vector<MemLimit*>& limits() { return limits_; }
  bool exceeded_limit() const { return exceeded_limit_; }

  // Return sum of chunk_sizes_.
  int64_t GetTotalChunkSizes() const;

  // Return logical offset of data ptr into allocated data (interval
  // [0, total_allocated_bytes()) ).
  // Returns -1 if 'data' doesn't belong to this mempool.
  int GetOffset(uint8_t* data);

  // Return logical offset of memory returned by next call to Allocate()
  // into allocated data.
  int GetCurrentOffset() const { return total_allocated_bytes_; }

  // Given a logical offset into the allocated data (allowed values:
  // 0 - total_allocated_bytes() - 1), return a pointer to that offset.
  uint8_t* GetDataPtr(int offset);

  // Return (data ptr, allocated bytes) pairs for all chunks owned by this mempool.
  void GetChunkInfo(std::vector<std::pair<uint8_t*, int> >* chunk_info);

  // Print allocated bytes from all chunks.
  std::string DebugPrint();
  
  // TODO: make a macro for doing this
  // For C++/IR interop, we need to be able to look up types by name.
  static const char* LLVM_CLASS_NAME;

 private:
  static const int DEFAULT_INITIAL_CHUNK_SIZE = 4 * 1024;
  static const int MAX_CHUNK_SIZE = 512 * 1024;

  struct ChunkInfo {
    bool owns_data;  // true if we eventually need to dealloc data
    uint8_t* data;
    int size;  // in bytes

    // number of bytes allocated via Allocate() up to but excluding this chunk;
    // *not* valid for chunks > current_chunk_idx_ (because that would create too
    // much maintenance work if we have trailing unoccupied chunks)
    int cumulative_allocated_bytes;

    // bytes allocated via Allocate() in this chunk
    int allocated_bytes;

    explicit ChunkInfo(int size);

    ChunkInfo()
      : owns_data(true),
        data(NULL),
        size(0),
        cumulative_allocated_bytes(0),
        allocated_bytes(0) {}
  };

  // chunk from which we served the last Allocate() call;
  // always points to the last chunk that contains allocated data;
  // chunks 0..current_chunk_idx_ are guaranteed to contain data
  // (chunks_[i].allocated_bytes > 0 for i: 0..current_chunk_idx_);
  // -1 if no chunks present
  int current_chunk_idx_;

  // chunk where last offset conversion (GetOffset() or GetDataPtr()) took place;
  // -1 if those functions have never been called
  int last_offset_conversion_chunk_idx_;

  int chunk_size_;  // if != 0, use this size for new chunks

  // sum of allocated_bytes_
  int64_t total_allocated_bytes_;

  // Maximum number of bytes allocated from this pool at one time.
  int64_t peak_allocated_bytes_;

  std::vector<ChunkInfo> chunks_;

  std::vector<MemLimit*> limits_;

  // true if one of the registered limits was exceeded during an Allocate()
  // call
  bool exceeded_limit_;

  // Find or allocated a chunk with at least min_size spare capacity and update
  // current_chunk_idx_. Also updates chunks_, chunk_sizes_ and allocated_bytes_
  // if a new chunk needs to be created.
  void FindChunk(int min_size);

  // Check integrity of the supporting data structures; always returns true but DCHECKs
  // all invariants.
  // If 'current_chunk_empty' is false, checks that the current chunk contains data.
  bool CheckIntegrity(bool current_chunk_empty);

  int GetOffsetHelper(uint8_t* data);
  uint8_t* GetDataPtrHelper(int offset);

  // Return offset to unoccpied space in current chunk.
  int GetFreeOffset() const {
    if (current_chunk_idx_ == -1) return 0;
    return chunks_[current_chunk_idx_].allocated_bytes;
  }
};

inline
int MemPool::GetOffset(uint8_t* data) {
  if (last_offset_conversion_chunk_idx_ != -1) {
    const ChunkInfo& info = chunks_[last_offset_conversion_chunk_idx_];
    if (info.data <= data && info.data + info.allocated_bytes > data) {
      return info.cumulative_allocated_bytes + data - info.data;
    }
  }
  return GetOffsetHelper(data);
}

inline
uint8_t* MemPool::GetDataPtr(int offset) {
  if (last_offset_conversion_chunk_idx_ != -1) {
    const ChunkInfo& info = chunks_[last_offset_conversion_chunk_idx_];
    if (info.cumulative_allocated_bytes <= offset
        && info.cumulative_allocated_bytes + info.allocated_bytes > offset) {
      return info.data + offset - info.cumulative_allocated_bytes;
    }
  }
  return GetDataPtrHelper(offset);
}

}

#endif

