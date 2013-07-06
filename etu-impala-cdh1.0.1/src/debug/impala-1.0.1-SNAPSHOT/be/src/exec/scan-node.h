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


#ifndef IMPALA_EXEC_SCAN_NODE_H_
#define IMPALA_EXEC_SCAN_NODE_H_

#include <string>
#include "exec/exec-node.h"
#include "util/runtime-profile.h"
#include "gen-cpp/ImpalaInternalService_types.h"

namespace impala {

class TScanRange;

// Abstract base class of all scan nodes; introduces SetScanRange().
//
// Includes ScanNode common counters:
//   BytesRead - total bytes read by this scan node
//
//   TotalRawHdfsReadTime - it measures the total time spent in the disk-io-mgr's reading
//     threads for this node. For example, if we have 3 reading threads and each spent
//     1 sec, this counter will report 3 sec.
//
//   TotalReadThroughput - BytesRead divided by the total time spent in this node
//     (from Open to Close). For IO bounded queries, this should be very close to the
//     total throughput of all the disks.
//
//   PerDiskRawHdfsThroughput - the read throughput for each disk. If all the data reside
//     on disk, this should be the read throughput the disk, regardless of whether the
//     query is IO bounded or not.
//
//   NumDisksAccessed - number of disks accessed.
//
//   AverageIoMgrQueueCapacity - the average queue capacity in the io mgr for this node.
//   AverageIoMgrQueueSize - the average queue size (for ready buffers) in the io mgr
//     for this node.
//
//   AverageScannerThreadConcurrency - the average number of active scanner threads. A
//     scanner thread is considered active if it is not blocked by IO. This number would
//     be low (less than 1) for IO-bound queries. For cpu-bound queries, this number
//     would be close to the max scanner threads allowed.
//
//   AverageScannerThreadConcurrency - the average number of active scanner threads. A
//     scanner thread is considered active if it is not blocked by IO. This number would
//     be low (less than 1) for IO bounded queries. For cpu bounded queries, this number
//     would be close to the max scanner threads allowed.
//
//   AverageHdfsReadThreadConcurrency - the average number of active hdfs reading threads
//     reading for this scan node. For IO bound queries, this should be close to the
//     number of disk.
//
//   Hdfs Read Thread Concurrency Bucket - the bucket counting (%) of hdfs read thread
//     concurrency.
//
//   ScanRangesComplete - number of scan ranges completed
//
//   MaterializeTupleTime - time spent in creating in-memory tuple format
//
//   ScannerThreadsTotalWallClockTime - total time spent in all scanner threads.
//
//   ScannerThreadsUserTime, ScannerThreadsSysTime,
//   ScannerThreadsVoluntaryContextSwitches, ScannerThreadsInvoluntaryContextSwitches -
//     these are aggregated counters across all scanner threads of this scan node. They
//     are taken from getrusage. See RuntimeProfile::ThreadCounters for details.
//
class ScanNode : public ExecNode {
 public:
  ScanNode(ObjectPool* pool, const TPlanNode& tnode, const DescriptorTbl& descs)
    : ExecNode(pool, tnode, descs),
      active_scanner_thread_counter_(TCounterType::UNIT, 0),
      active_hdfs_read_thread_counter_(TCounterType::UNIT, 0) {}

  // Set up counters
  virtual Status Prepare(RuntimeState* state);

  // Convert scan_ranges into node-specific scan restrictions.  This should be
  // called after Prepare()
  virtual Status SetScanRanges(const std::vector<TScanRangeParams>& scan_ranges) = 0;

  virtual bool IsScanNode() const { return true; }

  RuntimeProfile::Counter* bytes_read_counter() const { return bytes_read_counter_; }
  RuntimeProfile::Counter* rows_read_counter() const { return rows_read_counter_; }
  RuntimeProfile::Counter* read_timer() const { return read_timer_; }
  RuntimeProfile::Counter* total_throughput_counter() const {
    return total_throughput_counter_;
  }
  RuntimeProfile::Counter* per_read_thread_throughput_counter() const {
    return per_read_thread_throughput_counter_;
  }
  RuntimeProfile::Counter* materialize_tuple_timer() const {
    return materialize_tuple_timer_;
  }
  RuntimeProfile::Counter* scan_ranges_complete_counter() const {
    return scan_ranges_complete_counter_;
  }
  RuntimeProfile::ThreadCounters* scanner_thread_counters() const {
    return scanner_thread_counters_;
  }
  RuntimeProfile::Counter& active_scanner_thread_counter() {
    return active_scanner_thread_counter_;
  }
  RuntimeProfile::Counter* average_scanner_thread_concurrency() const {
    return average_scanner_thread_concurrency_;
  }

  // names of ScanNode common counters
  static const std::string BYTES_READ_COUNTER;
  static const std::string ROWS_READ_COUNTER;
  static const std::string TOTAL_READ_TIMER;
  static const std::string TOTAL_THROUGHPUT_COUNTER;
  static const std::string PER_READ_THREAD_THROUGHPUT_COUNTER;
  static const std::string NUM_DISKS_ACCESSED_COUNTER;
  static const std::string MATERIALIZE_TUPLE_TIMER;
  static const std::string SCAN_RANGES_COMPLETE_COUNTER;
  static const std::string SCANNER_THREAD_COUNTERS_PREFIX;
  static const std::string SCANNER_THREAD_TOTAL_WALLCLOCK_TIME;
  static const std::string AVERAGE_SCANNER_THREAD_CONCURRENCY;
  static const std::string AVERAGE_IO_MGR_QUEUE_CAPACITY;
  static const std::string AVERAGE_IO_MGR_QUEUE_SIZE;
  static const std::string AVERAGE_HDFS_READ_THREAD_CONCURRENCY;

 protected:
  RuntimeProfile::Counter* bytes_read_counter_; // # bytes read from the scanner
  // # rows/tuples read from the scanner (including those discarded by EvalConjucts())
  RuntimeProfile::Counter* rows_read_counter_;
  RuntimeProfile::Counter* read_timer_; // total read time
  // Wall based aggregate read throughput [bytes/sec]
  RuntimeProfile::Counter* total_throughput_counter_;
  // Per thread read throughput [bytes/sec]
  RuntimeProfile::Counter* per_read_thread_throughput_counter_;
  RuntimeProfile::Counter* num_disks_accessed_counter_;
  RuntimeProfile::Counter* materialize_tuple_timer_;  // time writing tuple slots
  RuntimeProfile::Counter* scan_ranges_complete_counter_;
  // Aggregated scanner thread counters
  RuntimeProfile::ThreadCounters* scanner_thread_counters_;

  // The number of active scanner threads that are not blocked by IO.
  RuntimeProfile::Counter active_scanner_thread_counter_;

  // Average number of active scanner threads
  // This should be created in Open and stopped when all the scanner threads are done.
  RuntimeProfile::Counter* average_scanner_thread_concurrency_;

  // The number of active hdfs reading threads reading for this node.
  RuntimeProfile::Counter active_hdfs_read_thread_counter_;

  // Average number of active hdfs reading threads
  // This should be created in Open and stopped when all the scanner threads are done.
  RuntimeProfile::Counter* average_hdfs_read_thread_concurrency_;

  // HDFS read thread concurrency bucket: bucket[i] refers to the number of sample
  // taken where there are i concurrent hdfs read thread running
  std::vector<RuntimeProfile::Counter*> hdfs_read_thread_concurrency_bucket_;
};

}

#endif
