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


#ifndef IMPALA_EXEC_MERGE_NODE_H_
#define IMPALA_EXEC_MERGE_NODE_H_

#include <boost/scoped_ptr.hpp>

#include "exec/exec-node.h"
#include "runtime/mem-pool.h"
#include <boost/scoped_ptr.hpp>

namespace impala {

class Tuple;
class TupleRow;

// Node that merges the results of its children by materializing their
// evaluated expressions into row batches. The MergeNode pulls row batches sequentially
// from its children sequentially, i.e., it exhausts one child completely before moving
// on to the next one.
class MergeNode : public ExecNode {
 public:
  MergeNode(ObjectPool* pool, const TPlanNode& tnode, const DescriptorTbl& descs);

  virtual Status Prepare(RuntimeState* state);
  virtual Status Open(RuntimeState* state);
  virtual Status GetNext(RuntimeState* state, RowBatch* row_batch, bool* eos);
  virtual Status Close(RuntimeState* state);

 private:
  const static int INVALID_CHILD_IDX = -1;

  // Tuple id resolved in Prepare() to set tuple_desc_;
  int tuple_id_;

  // Descriptor for tuples this merge node constructs.
  const TupleDescriptor* tuple_desc_;

  // Const exprs materialized by this node. These exprs don't refer to any children.
  std::vector<std::vector<Expr*> > const_result_expr_lists_;

  // Index of current const result expr list.
  int const_result_expr_idx_;

  // Exprs materialized by this node. The i-th result expr list refers to the i-th child.
  std::vector<std::vector<Expr*> > result_expr_lists_;

  // Index of current child.
  int child_idx_;

  // Current row batch of current child. We reset the pointer to a new RowBatch
  // when switching to a different child.
  boost::scoped_ptr<RowBatch> child_row_batch_;

  // Saved from the last to GetNext() on the current child.
  bool child_eos_;

  // Index of current row in child_row_batch_.
  int child_row_idx_;

  // Create const exprs, child exprs and conjuncts from corresponding thrift exprs.
  Status Init(ObjectPool* pool, const TPlanNode& tnode);

  // Evaluates exprs on all rows in child_row_batch_ starting from child_row_idx_,
  // and materializes their results into *tuple.
  // Adds *tuple into row_batch, and increments *tuple.
  // If const_exprs is true, then the exprs are evaluated exactly once without
  // fetching rows from child_row_batch_.
  // Only commits tuples to row_batch if they are not filtered by conjuncts.
  // Returns true if row_batch should be returned to caller or limit has been
  // reached, false otherwise.
  bool EvalAndMaterializeExprs(const std::vector<Expr*>& exprs, bool const_exprs,
      Tuple** tuple, RowBatch* row_batch);
};

}

#endif
