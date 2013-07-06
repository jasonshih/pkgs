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

#include "runtime/plan-fragment-executor.h"

#include <thrift/protocol/TDebugProtocol.h>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/unordered_map.hpp>
#include <boost/foreach.hpp>

#include "codegen/llvm-codegen.h"
#include "common/logging.h"
#include "common/object-pool.h"
#include "exec/data-sink.h"
#include "exec/exec-node.h"
#include "exec/exchange-node.h"
#include "exec/scan-node.h"
#include "exec/hdfs-scan-node.h"
#include "exec/hbase-table-scanner.h"
#include "exprs/expr.h"
#include "runtime/descriptors.h"
#include "runtime/data-stream-mgr.h"
#include "runtime/row-batch.h"
#include "runtime/mem-limit.h"
#include "util/cpu-info.h"
#include "util/debug-util.h"
#include "util/container-util.h"
#include "util/parse-util.h"
#include "util/mem-info.h"

DEFINE_bool(serialize_batch, false, "serialize and deserialize each returned row batch");
DEFINE_int32(status_report_interval, 5, "interval between profile reports; in seconds");

using namespace std;
using namespace boost;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

namespace impala {

PlanFragmentExecutor::PlanFragmentExecutor(
    ExecEnv* exec_env, const ReportStatusCallback& report_status_cb)
  : exec_env_(exec_env),
    report_status_cb_(report_status_cb),
    report_thread_active_(false),
    done_(false),
    prepared_(false),
    closed_(false),
    has_thread_token_(false) {
}

PlanFragmentExecutor::~PlanFragmentExecutor() {
  Close();
  // at this point, the report thread should have been stopped
  DCHECK(!report_thread_active_);
}

Status PlanFragmentExecutor::Prepare(const TExecPlanFragmentParams& request) {
  const TPlanFragmentExecParams& params = request.params;
  query_id_ = params.query_id;

  VLOG_QUERY << "Prepare(): query_id=" << PrintId(query_id_)
             << " instance_id=" << PrintId(params.fragment_instance_id);
  VLOG(2) << "params:\n" << ThriftDebugString(params);

  runtime_state_.reset(
      new RuntimeState(params.fragment_instance_id, request.query_options,
        request.query_globals.now_string, exec_env_));

  // Reserve one main thread from the pool
  runtime_state_->resource_pool()->AcquireThreadToken();
  has_thread_token_ = true;

  average_thread_tokens_ = profile()->AddSamplingCounter("AverageThreadTokens",
      bind<int64_t>(mem_fn(&ThreadResourceMgr::ResourcePool::num_threads),
          runtime_state_->resource_pool()));

  if (exec_env_->mem_limit() != NULL) {
    // we have a global limit
    runtime_state_->mem_limits()->push_back(exec_env_->mem_limit());
  }
  if (request.query_options.mem_limit > 0) {
    // we have a per-query limit
    int64_t bytes_limit = request.query_options.mem_limit;
    mem_limit_.reset(new MemLimit(bytes_limit));
    runtime_state_->SetFragmentMemLimit(mem_limit_.get());
    if (bytes_limit > MemInfo::physical_mem()) {
      LOG(WARNING) << "Memory limit "
                   << PrettyPrinter::Print(bytes_limit, TCounterType::BYTES)
                   << " exceeds physical memory of "
                   << PrettyPrinter::Print(MemInfo::physical_mem(), TCounterType::BYTES);
    }
    VLOG_QUERY << "Using query memory limit: "
               << PrettyPrinter::Print(bytes_limit, TCounterType::BYTES);
  }

  // set up desc tbl
  DescriptorTbl* desc_tbl = NULL;
  DCHECK(request.__isset.desc_tbl);
  RETURN_IF_ERROR(DescriptorTbl::Create(obj_pool(), request.desc_tbl, &desc_tbl));
  runtime_state_->set_desc_tbl(desc_tbl);
  VLOG_QUERY << "descriptor table for fragment=" << params.fragment_instance_id << "\n"
             << desc_tbl->DebugString();

  // set up plan
  DCHECK(request.__isset.fragment);
  RETURN_IF_ERROR(
      ExecNode::CreateTree(obj_pool(), request.fragment.plan, *desc_tbl, &plan_));

  if (request.params.__isset.debug_node_id) {
    DCHECK(request.params.__isset.debug_action);
    DCHECK(request.params.__isset.debug_phase);
    ExecNode::SetDebugOptions(
        request.params.debug_node_id, request.params.debug_phase,
        request.params.debug_action, plan_);
  }

  // set #senders of exchange nodes before calling Prepare()
  vector<ExecNode*> exch_nodes;
  plan_->CollectNodes(TPlanNodeType::EXCHANGE_NODE, &exch_nodes);
  BOOST_FOREACH(ExecNode* exch_node, exch_nodes) {
    DCHECK_EQ(exch_node->type(), TPlanNodeType::EXCHANGE_NODE);
    int num_senders = FindWithDefault(params.per_exch_num_senders, exch_node->id(), 0);
    DCHECK_GT(num_senders, 0);
    static_cast<ExchangeNode*>(exch_node)->set_num_senders(num_senders);
  }

  RETURN_IF_ERROR(plan_->Prepare(runtime_state_.get()));

  // set scan ranges
  vector<ExecNode*> scan_nodes;
  vector<TScanRangeParams> no_scan_ranges;
  plan_->CollectScanNodes(&scan_nodes);
  for (int i = 0; i < scan_nodes.size(); ++i) {
    ScanNode* scan_node = static_cast<ScanNode*>(scan_nodes[i]);
    const vector<TScanRangeParams>& scan_ranges =
        FindWithDefault(params.per_node_scan_ranges, scan_node->id(), no_scan_ranges);
    scan_node->SetScanRanges(scan_ranges);
  }

  PrintVolumeIds(params.per_node_scan_ranges);

  // set up sink, if required
  if (request.fragment.__isset.output_sink) {
    RETURN_IF_ERROR(DataSink::CreateDataSink(obj_pool(),
        request.fragment.output_sink, request.fragment.output_exprs, params,
        row_desc(), &sink_));
    RETURN_IF_ERROR(sink_->Init(runtime_state()));

    RuntimeProfile* sink_profile = sink_->profile();
    if (sink_profile != NULL) {
      profile()->AddChild(sink_profile);
    }
  } else {
    sink_.reset(NULL);
  }

  // set up profile counters
  profile()->AddChild(plan_->runtime_profile());
  rows_produced_counter_ = ADD_COUNTER(profile(), "RowsProduced", TCounterType::UNIT);

  row_batch_.reset(new RowBatch(
      plan_->row_desc(), runtime_state_->batch_size(), *runtime_state_->mem_limits()));
  VLOG(3) << "plan_root=\n" << plan_->DebugString();
  prepared_ = true;
  return Status::OK;
}

void PlanFragmentExecutor::OptimizeLlvmModule() {
  if (runtime_state_->llvm_codegen() == NULL) return;
  Status status = runtime_state_->llvm_codegen()->OptimizeModule();
  if (!status.ok()) {
    LOG(ERROR) << "Error with codegen for this query: " << status.GetErrorMsg();
    // TODO: propagate this to the coordinator and user?  Not really actionable
    // for them but we'd like them to let us know.
  }
}

void PlanFragmentExecutor::PrintVolumeIds(
    const PerNodeScanRanges& per_node_scan_ranges) {
  if (per_node_scan_ranges.empty()) return;

  HdfsScanNode::PerVolumnStats per_volume_stats;
  BOOST_FOREACH(const PerNodeScanRanges::value_type& entry, per_node_scan_ranges) {
    HdfsScanNode::UpdateHdfsSplitStats(entry.second, &per_volume_stats);
  }

  stringstream str;

  HdfsScanNode::PrintHdfsSplitStats(per_volume_stats, &str);
  profile()->AddInfoString(HdfsScanNode::HDFS_SPLIT_STATS_DESC, str.str());
  VLOG_FILE << "Hdfs split stats (<volume id>:<# splits>/<split lengths>) for query="
            << query_id_ << ":\n"
            << str.str();
}

Status PlanFragmentExecutor::Open() {
  VLOG_QUERY << "Open(): instance_id=" << runtime_state_->fragment_instance_id();
  // we need to start the profile-reporting thread before calling Open(), since it
  // may block
  // TODO: if no report thread is started, make sure to send a final profile
  // at end, otherwise the coordinator hangs in case we finish w/ an error
  if (!report_status_cb_.empty() && FLAGS_status_report_interval > 0) {
    unique_lock<mutex> l(report_thread_lock_);
    report_thread_ = thread(&PlanFragmentExecutor::ReportProfile, this);
    // make sure the thread started up, otherwise ReportProfile() might get into a race
    // with StopReportThread()
    report_thread_started_cv_.wait(l);
    report_thread_active_ = true;
  }

  Status status = OpenInternal();
  if (!status.ok() && !status.IsCancelled() && runtime_state_->LogHasSpace()) {
    // Log error message in addition to returning in Status. Queries that do not
    // fetch results (e.g. insert) may not receive the message directly and can
    // only retrieve the log.
    runtime_state_->LogError(status.GetErrorMsg());
  }
  UpdateStatus(status);
  return status;
}

Status PlanFragmentExecutor::OpenInternal() {
  {
    SCOPED_TIMER(profile()->total_time_counter());
    RETURN_IF_ERROR(plan_->Open(runtime_state_.get()));
  }

  if (sink_.get() == NULL) return Status::OK;

  // If there is a sink, do all the work of driving it here, so that
  // when this returns the query has actually finished
  RowBatch* batch;
  while (true) {
    RETURN_IF_ERROR(GetNextInternal(&batch));
    if (batch == NULL) break;
    if (VLOG_ROW_IS_ON) {
      VLOG_ROW << "OpenInternal: #rows=" << batch->num_rows();
      for (int i = 0; i < batch->num_rows(); ++i) {
        TupleRow* row = batch->GetRow(i);
        VLOG_ROW << PrintRow(row, row_desc());
      }
    }

    SCOPED_TIMER(profile()->total_time_counter());
    RETURN_IF_ERROR(sink_->Send(runtime_state(), batch));
  }

  // Close the sink *before* stopping the report thread. Close may
  // need to add some important information to the last report that
  // gets sent. (e.g. table sinks record the files they have written
  // to in this method)
  // The coordinator report channel waits until all backends are
  // either in error or have returned a status report with done =
  // true, so tearing down any data stream state (a separate
  // channel) in Close is safe.

  // TODO: If this returns an error, the d'tor will call Close again. We should
  // audit the sinks to check that this is ok, or change that behaviour.
  RETURN_IF_ERROR(sink_->Close(runtime_state()));

  // Setting to NULL ensures that the d'tor won't double-close the sink.
  sink_.reset(NULL);
  done_ = true;

  ReleaseThreadToken();

  StopReportThread();
  SendReport(true);

  return Status::OK;
}

void PlanFragmentExecutor::ReportProfile() {
  VLOG_FILE << "ReportProfile(): instance_id="
            << runtime_state_->fragment_instance_id();
  DCHECK(!report_status_cb_.empty());
  unique_lock<mutex> l(report_thread_lock_);
  // tell Open() that we started
  report_thread_started_cv_.notify_one();

  // Jitter the reporting time of remote fragments by a random amount between
  // 0 and the report_interval.  This way, the coordinator doesn't get all the
  // updates at once so its better for contention as well as smoother progress
  // reporting.
  int report_fragment_offset = rand() % FLAGS_status_report_interval;
  system_time timeout =
      get_system_time() + posix_time::seconds(report_fragment_offset);
  // We don't want to wait longer than it takes to run the entire fragment.
  stop_report_thread_cv_.timed_wait(l, timeout);

  while (report_thread_active_) {
    system_time timeout =
        get_system_time() + posix_time::seconds(FLAGS_status_report_interval);

    // timed_wait can return because the timeout occurred or the condition variable
    // was signaled.  We can't rely on its return value to distinguish between the
    // two cases (e.g. there is a race here where the wait timed out but before grabbing
    // the lock, the condition variable was signaled).  Instead, we will use an external
    // flag, report_thread_active_, to coordinate this.
    stop_report_thread_cv_.timed_wait(l, timeout);

    if (VLOG_FILE_IS_ON) {
      VLOG_FILE << "Reporting " << (!report_thread_active_ ? "final " : " ")
                << "profile for instance " << runtime_state_->fragment_instance_id();
      stringstream ss;
      profile()->PrettyPrint(&ss);
      VLOG_FILE << ss.str();
    }

    if (!report_thread_active_) break;
    SendReport(false);
  }

  VLOG_FILE << "exiting reporting thread: instance_id="
            << runtime_state_->fragment_instance_id();
}

void PlanFragmentExecutor::SendReport(bool done) {
  if (report_status_cb_.empty()) return;

  Status status;
  {
    lock_guard<mutex> l(status_lock_);
    status = status_;
  }
  // This will send a report even if we are cancelled.  If the query completed correctly
  // but fragments still need to be cancelled (e.g. limit reached), the coordinator will
  // be waiting for a final report and profile.
  report_status_cb_(status, profile(), done || !status.ok());
}

void PlanFragmentExecutor::StopReportThread() {
  if (!report_thread_active_) return;
  {
    lock_guard<mutex> l(report_thread_lock_);
    report_thread_active_ = false;
  }
  stop_report_thread_cv_.notify_one();
  report_thread_.join();
}

Status PlanFragmentExecutor::GetNext(RowBatch** batch) {
  VLOG_FILE << "GetNext(): instance_id=" << runtime_state_->fragment_instance_id();
  Status status = GetNextInternal(batch);
  UpdateStatus(status);
  if (done_) {
    VLOG_QUERY << "Finished executing fragment query_id=" << PrintId(query_id_)
               << " instance_id=" << PrintId(runtime_state_->fragment_instance_id());
    // Query is done, return the thread token
    ReleaseThreadToken();
    StopReportThread();
    SendReport(true);
  }

  return status;
}

Status PlanFragmentExecutor::GetNextInternal(RowBatch** batch) {
  if (done_) {
    *batch = NULL;
    return Status::OK;
  }

  while (!done_) {
    row_batch_->Reset();
    SCOPED_TIMER(profile()->total_time_counter());
    RETURN_IF_ERROR(plan_->GetNext(runtime_state_.get(), row_batch_.get(), &done_));
    if (row_batch_->num_rows() > 0) {
      COUNTER_UPDATE(rows_produced_counter_, row_batch_->num_rows());
      *batch = row_batch_.get();
      break;
    }
    *batch = NULL;
  }

  return Status::OK;
}

void PlanFragmentExecutor::UpdateStatus(const Status& status) {
  if (status.ok()) return;
  {
    lock_guard<mutex> l(status_lock_);
    if (status_.ok()) status_ = status;
  }
  StopReportThread();
  SendReport(true);
}

void PlanFragmentExecutor::Cancel() {
  VLOG_QUERY << "Cancel(): instance_id=" << runtime_state_->fragment_instance_id();
  DCHECK(prepared_);
  runtime_state_->set_is_cancelled(true);
  runtime_state_->stream_mgr()->Cancel(runtime_state_->fragment_instance_id());
}

const RowDescriptor& PlanFragmentExecutor::row_desc() {
  return plan_->row_desc();
}

RuntimeProfile* PlanFragmentExecutor::profile() {
  return runtime_state_->runtime_profile();
}

bool PlanFragmentExecutor::ReachedLimit() {
  return plan_->ReachedLimit();
}

void PlanFragmentExecutor::ReleaseThreadToken() {
  if (has_thread_token_) {
    has_thread_token_ = false;
    runtime_state_->resource_pool()->ReleaseThreadToken(true);
    profile()->StopSamplingCounterUpdates(average_thread_tokens_);
  }
}

void PlanFragmentExecutor::Close() {
  if (closed_) return;
  row_batch_.reset(NULL);
  // Prepare may not have been called, which sets runtime_state_
  if (runtime_state_.get() != NULL) {
    plan_->Close(runtime_state_.get());
    if (sink_.get() != NULL) {
      sink_->Close(runtime_state());
    }
    exec_env_->thread_mgr()->UnregisterPool(runtime_state_->resource_pool());
  }
  closed_ = true;
}

}
