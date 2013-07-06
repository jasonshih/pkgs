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


#ifndef IMPALA_EXEC_EXCHANGE_NODE_H
#define IMPALA_EXEC_EXCHANGE_NODE_H

#include <boost/scoped_ptr.hpp>
#include "exec/exec-node.h"

namespace impala {

class RowBatch;
class DataStreamRecvr;

// Receiver node for data streams. This simply feeds row batches received from the
// data stream into the execution tree.
// The data stream is created in Prepare() and closed in the d'tor.
class ExchangeNode : public ExecNode {
 public:
  ExchangeNode(ObjectPool* pool, const TPlanNode& tnode, const DescriptorTbl& descs);

  virtual Status Prepare(RuntimeState* state);
  virtual Status Open(RuntimeState* state);
  virtual Status GetNext(RuntimeState* state, RowBatch* row_batch, bool* eos);

  // the number of senders needs to be set after the c'tor, because it's not
  // recorded in TPlanNode, and before calling Prepare()
  void set_num_senders(int num_senders) { num_senders_ = num_senders; }

 protected:
  virtual void DebugString(int indentation_level, std::stringstream* out) const;

 private:
  int num_senders_;  // needed for stream_recvr_ construction

  // created in Prepare() and owned by the RuntimeState
  DataStreamRecvr* stream_recvr_;

  // our input rows are a prefix of the rows we produce
  RowDescriptor input_row_desc_;

  // the size of our input batches does not necessarily match the capacity
  // of our output batches, which means that we need to buffer the input
  boost::scoped_ptr<RowBatch> input_batch_;

  int next_row_idx_;  // next row to copy
  
  // time spent reconstructing received rows
  RuntimeProfile::Counter* convert_row_batch_timer_;   
};

};

#endif

