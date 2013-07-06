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

#include <sstream>
#include "exprs/agg-expr.h"
#include "util/debug-util.h"
#include "gen-cpp/Exprs_types.h"
#include "codegen/llvm-codegen.h"

using namespace std;
using namespace llvm;

namespace impala {

AggregateExpr::AggregateExpr(const TExprNode& node)
  : Expr(node),
    agg_op_(node.agg_expr.op),
    is_star_(node.agg_expr.is_star),
    is_distinct_(node.agg_expr.is_distinct) {
}

Status AggregateExpr::Prepare(RuntimeState* state, const RowDescriptor& desc) {
  RETURN_IF_ERROR(Expr::PrepareChildren(state, desc));
  if (agg_op_ == TAggregationOp::INVALID) {
    stringstream out;
    out << "AggregateExpr::Prepare: Invalid aggregation op: " << agg_op_;
    return Status(out.str());
  }
  return Status::OK;
}

string AggregateExpr::DebugString() const {
  stringstream out;
  out << "AggExpr(op= " << agg_op_ << " star=" << is_star_ 
      << " distinct=" << is_distinct_
      << " " << Expr::DebugString() << ")";
  return out.str();
}

// AggregateExpr doesn't have a compute function.  Just return the child function.
Function* AggregateExpr::Codegen(LlvmCodeGen* codegen) {
  DCHECK_LE(GetNumChildren(), 1); // count(*) has no children
  if (GetNumChildren() == 0) {
    scratch_buffer_size_ = 0;
    return NULL;
  } else {
    codegen_fn_ = children()[0]->Codegen(codegen);
    scratch_buffer_size_ = children()[0]->scratch_buffer_size();
    return codegen_fn_;
  }
}

}

