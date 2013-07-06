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

#include "exec/aggregation-node.h"

#include "exec/hash-table.inline.h"
#include "runtime/row-batch.h"
#include "runtime/runtime-state.h"
#include "runtime/tuple.h"
#include "runtime/tuple-row.h"

using namespace impala;

// Functions in this file are cross compiled to IR with clang.  These functions
// are modified at runtime with a query specific codegen'd UpdateAggTuple

void AggregationNode::ProcessRowBatchNoGrouping(RowBatch* batch) {
  for (int i = 0; i < batch->num_rows(); ++i) {
    UpdateAggTuple(singleton_output_tuple_, batch->GetRow(i));
  }
}

void AggregationNode::ProcessRowBatchWithGrouping(RowBatch* batch) {
  for (int i = 0; i < batch->num_rows(); ++i) {
    TupleRow* row = batch->GetRow(i);
    AggregationTuple* agg_tuple = NULL; 
    HashTable::Iterator entry = hash_tbl_->Find(row);
    if (!entry.HasNext()) {
      agg_tuple = ConstructAggTuple();
      hash_tbl_->Insert(reinterpret_cast<TupleRow*>(&agg_tuple));
    } else {
      agg_tuple = reinterpret_cast<AggregationTuple*>(entry.GetRow()->GetTuple(0));
    }
    UpdateAggTuple(agg_tuple, row);
  }
}

