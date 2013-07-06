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

// This is a generated file, DO NOT EDIT.
// To add new functions, see impala/common/function-registry/gen_opcodes.py

#include "opcode/functions.h"
#include "exprs/expr.h"
#include "exprs/case-expr.h"
#include "runtime/string-value.inline.h"
#include "runtime/tuple-row.h"
#include "util/string-parser.h"
#include <boost/lexical_cast.hpp>

using namespace boost;
using namespace std;

namespace impala { 

void* ComputeFunctions::Add_long_long(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int64_t* val1 = reinterpret_cast<int64_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int64_t* val2 = reinterpret_cast<int64_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bigint_val = (*val1 + *val2);
  return &e->result_.bigint_val;
}

void* ComputeFunctions::Add_double_double(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  double* val1 = reinterpret_cast<double*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  double* val2 = reinterpret_cast<double*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.double_val = (*val1 + *val2);
  return &e->result_.double_val;
}

void* ComputeFunctions::Subtract_long_long(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int64_t* val1 = reinterpret_cast<int64_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int64_t* val2 = reinterpret_cast<int64_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bigint_val = (*val1 - *val2);
  return &e->result_.bigint_val;
}

void* ComputeFunctions::Subtract_double_double(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  double* val1 = reinterpret_cast<double*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  double* val2 = reinterpret_cast<double*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.double_val = (*val1 - *val2);
  return &e->result_.double_val;
}

void* ComputeFunctions::Multiply_long_long(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int64_t* val1 = reinterpret_cast<int64_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int64_t* val2 = reinterpret_cast<int64_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bigint_val = (*val1 * *val2);
  return &e->result_.bigint_val;
}

void* ComputeFunctions::Multiply_double_double(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  double* val1 = reinterpret_cast<double*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  double* val2 = reinterpret_cast<double*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.double_val = (*val1 * *val2);
  return &e->result_.double_val;
}

void* ComputeFunctions::Divide_double_double(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  double* val1 = reinterpret_cast<double*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  double* val2 = reinterpret_cast<double*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.double_val = (*val1 / *val2);
  return &e->result_.double_val;
}

void* ComputeFunctions::Int_Divide_char_char(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int8_t* val1 = reinterpret_cast<int8_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int8_t* val2 = reinterpret_cast<int8_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL || *val2 == 0) return NULL;
  e->result_.tinyint_val = (*val1 / *val2);
  return &e->result_.tinyint_val;
}

void* ComputeFunctions::Int_Divide_short_short(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int16_t* val1 = reinterpret_cast<int16_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int16_t* val2 = reinterpret_cast<int16_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL || *val2 == 0) return NULL;
  e->result_.smallint_val = (*val1 / *val2);
  return &e->result_.smallint_val;
}

void* ComputeFunctions::Int_Divide_int_int(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int32_t* val1 = reinterpret_cast<int32_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int32_t* val2 = reinterpret_cast<int32_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL || *val2 == 0) return NULL;
  e->result_.int_val = (*val1 / *val2);
  return &e->result_.int_val;
}

void* ComputeFunctions::Int_Divide_long_long(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int64_t* val1 = reinterpret_cast<int64_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int64_t* val2 = reinterpret_cast<int64_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL || *val2 == 0) return NULL;
  e->result_.bigint_val = (*val1 / *val2);
  return &e->result_.bigint_val;
}

void* ComputeFunctions::Mod_char_char(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int8_t* val1 = reinterpret_cast<int8_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int8_t* val2 = reinterpret_cast<int8_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL || *val2 == 0) return NULL;
  e->result_.tinyint_val = (*val1 % *val2);
  return &e->result_.tinyint_val;
}

void* ComputeFunctions::Mod_short_short(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int16_t* val1 = reinterpret_cast<int16_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int16_t* val2 = reinterpret_cast<int16_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL || *val2 == 0) return NULL;
  e->result_.smallint_val = (*val1 % *val2);
  return &e->result_.smallint_val;
}

void* ComputeFunctions::Mod_int_int(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int32_t* val1 = reinterpret_cast<int32_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int32_t* val2 = reinterpret_cast<int32_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL || *val2 == 0) return NULL;
  e->result_.int_val = (*val1 % *val2);
  return &e->result_.int_val;
}

void* ComputeFunctions::Mod_long_long(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int64_t* val1 = reinterpret_cast<int64_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int64_t* val2 = reinterpret_cast<int64_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL || *val2 == 0) return NULL;
  e->result_.bigint_val = (*val1 % *val2);
  return &e->result_.bigint_val;
}

void* ComputeFunctions::BitAnd_char_char(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int8_t* val1 = reinterpret_cast<int8_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int8_t* val2 = reinterpret_cast<int8_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.tinyint_val = (*val1 & *val2);
  return &e->result_.tinyint_val;
}

void* ComputeFunctions::BitAnd_short_short(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int16_t* val1 = reinterpret_cast<int16_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int16_t* val2 = reinterpret_cast<int16_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.smallint_val = (*val1 & *val2);
  return &e->result_.smallint_val;
}

void* ComputeFunctions::BitAnd_int_int(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int32_t* val1 = reinterpret_cast<int32_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int32_t* val2 = reinterpret_cast<int32_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.int_val = (*val1 & *val2);
  return &e->result_.int_val;
}

void* ComputeFunctions::BitAnd_long_long(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int64_t* val1 = reinterpret_cast<int64_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int64_t* val2 = reinterpret_cast<int64_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bigint_val = (*val1 & *val2);
  return &e->result_.bigint_val;
}

void* ComputeFunctions::BitXor_char_char(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int8_t* val1 = reinterpret_cast<int8_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int8_t* val2 = reinterpret_cast<int8_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.tinyint_val = (*val1 ^ *val2);
  return &e->result_.tinyint_val;
}

void* ComputeFunctions::BitXor_short_short(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int16_t* val1 = reinterpret_cast<int16_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int16_t* val2 = reinterpret_cast<int16_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.smallint_val = (*val1 ^ *val2);
  return &e->result_.smallint_val;
}

void* ComputeFunctions::BitXor_int_int(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int32_t* val1 = reinterpret_cast<int32_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int32_t* val2 = reinterpret_cast<int32_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.int_val = (*val1 ^ *val2);
  return &e->result_.int_val;
}

void* ComputeFunctions::BitXor_long_long(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int64_t* val1 = reinterpret_cast<int64_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int64_t* val2 = reinterpret_cast<int64_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bigint_val = (*val1 ^ *val2);
  return &e->result_.bigint_val;
}

void* ComputeFunctions::BitOr_char_char(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int8_t* val1 = reinterpret_cast<int8_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int8_t* val2 = reinterpret_cast<int8_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.tinyint_val = (*val1 | *val2);
  return &e->result_.tinyint_val;
}

void* ComputeFunctions::BitOr_short_short(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int16_t* val1 = reinterpret_cast<int16_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int16_t* val2 = reinterpret_cast<int16_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.smallint_val = (*val1 | *val2);
  return &e->result_.smallint_val;
}

void* ComputeFunctions::BitOr_int_int(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int32_t* val1 = reinterpret_cast<int32_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int32_t* val2 = reinterpret_cast<int32_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.int_val = (*val1 | *val2);
  return &e->result_.int_val;
}

void* ComputeFunctions::BitOr_long_long(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int64_t* val1 = reinterpret_cast<int64_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int64_t* val2 = reinterpret_cast<int64_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bigint_val = (*val1 | *val2);
  return &e->result_.bigint_val;
}

void* ComputeFunctions::BitNot_char(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int8_t* val = reinterpret_cast<int8_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.tinyint_val = ~ *val;
  return &e->result_.tinyint_val;
}

void* ComputeFunctions::BitNot_short(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int16_t* val = reinterpret_cast<int16_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.smallint_val = ~ *val;
  return &e->result_.smallint_val;
}

void* ComputeFunctions::BitNot_int(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int32_t* val = reinterpret_cast<int32_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.int_val = ~ *val;
  return &e->result_.int_val;
}

void* ComputeFunctions::BitNot_long(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int64_t* val = reinterpret_cast<int64_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bigint_val = ~ *val;
  return &e->result_.bigint_val;
}

void* ComputeFunctions::Eq_bool_bool(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  bool* val1 = reinterpret_cast<bool*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  bool* val2 = reinterpret_cast<bool*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 == *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Eq_char_char(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int8_t* val1 = reinterpret_cast<int8_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int8_t* val2 = reinterpret_cast<int8_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 == *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Eq_short_short(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int16_t* val1 = reinterpret_cast<int16_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int16_t* val2 = reinterpret_cast<int16_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 == *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Eq_int_int(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int32_t* val1 = reinterpret_cast<int32_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int32_t* val2 = reinterpret_cast<int32_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 == *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Eq_long_long(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int64_t* val1 = reinterpret_cast<int64_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int64_t* val2 = reinterpret_cast<int64_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 == *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Eq_float_float(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  float* val1 = reinterpret_cast<float*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  float* val2 = reinterpret_cast<float*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 == *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Eq_double_double(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  double* val1 = reinterpret_cast<double*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  double* val2 = reinterpret_cast<double*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 == *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ne_bool_bool(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  bool* val1 = reinterpret_cast<bool*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  bool* val2 = reinterpret_cast<bool*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 != *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ne_char_char(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int8_t* val1 = reinterpret_cast<int8_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int8_t* val2 = reinterpret_cast<int8_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 != *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ne_short_short(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int16_t* val1 = reinterpret_cast<int16_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int16_t* val2 = reinterpret_cast<int16_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 != *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ne_int_int(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int32_t* val1 = reinterpret_cast<int32_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int32_t* val2 = reinterpret_cast<int32_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 != *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ne_long_long(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int64_t* val1 = reinterpret_cast<int64_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int64_t* val2 = reinterpret_cast<int64_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 != *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ne_float_float(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  float* val1 = reinterpret_cast<float*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  float* val2 = reinterpret_cast<float*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 != *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ne_double_double(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  double* val1 = reinterpret_cast<double*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  double* val2 = reinterpret_cast<double*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 != *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Gt_bool_bool(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  bool* val1 = reinterpret_cast<bool*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  bool* val2 = reinterpret_cast<bool*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 > *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Gt_char_char(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int8_t* val1 = reinterpret_cast<int8_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int8_t* val2 = reinterpret_cast<int8_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 > *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Gt_short_short(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int16_t* val1 = reinterpret_cast<int16_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int16_t* val2 = reinterpret_cast<int16_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 > *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Gt_int_int(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int32_t* val1 = reinterpret_cast<int32_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int32_t* val2 = reinterpret_cast<int32_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 > *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Gt_long_long(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int64_t* val1 = reinterpret_cast<int64_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int64_t* val2 = reinterpret_cast<int64_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 > *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Gt_float_float(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  float* val1 = reinterpret_cast<float*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  float* val2 = reinterpret_cast<float*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 > *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Gt_double_double(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  double* val1 = reinterpret_cast<double*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  double* val2 = reinterpret_cast<double*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 > *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Lt_bool_bool(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  bool* val1 = reinterpret_cast<bool*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  bool* val2 = reinterpret_cast<bool*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 < *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Lt_char_char(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int8_t* val1 = reinterpret_cast<int8_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int8_t* val2 = reinterpret_cast<int8_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 < *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Lt_short_short(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int16_t* val1 = reinterpret_cast<int16_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int16_t* val2 = reinterpret_cast<int16_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 < *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Lt_int_int(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int32_t* val1 = reinterpret_cast<int32_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int32_t* val2 = reinterpret_cast<int32_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 < *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Lt_long_long(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int64_t* val1 = reinterpret_cast<int64_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int64_t* val2 = reinterpret_cast<int64_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 < *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Lt_float_float(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  float* val1 = reinterpret_cast<float*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  float* val2 = reinterpret_cast<float*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 < *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Lt_double_double(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  double* val1 = reinterpret_cast<double*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  double* val2 = reinterpret_cast<double*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 < *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ge_bool_bool(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  bool* val1 = reinterpret_cast<bool*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  bool* val2 = reinterpret_cast<bool*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 >= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ge_char_char(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int8_t* val1 = reinterpret_cast<int8_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int8_t* val2 = reinterpret_cast<int8_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 >= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ge_short_short(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int16_t* val1 = reinterpret_cast<int16_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int16_t* val2 = reinterpret_cast<int16_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 >= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ge_int_int(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int32_t* val1 = reinterpret_cast<int32_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int32_t* val2 = reinterpret_cast<int32_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 >= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ge_long_long(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int64_t* val1 = reinterpret_cast<int64_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int64_t* val2 = reinterpret_cast<int64_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 >= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ge_float_float(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  float* val1 = reinterpret_cast<float*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  float* val2 = reinterpret_cast<float*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 >= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ge_double_double(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  double* val1 = reinterpret_cast<double*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  double* val2 = reinterpret_cast<double*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 >= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Le_bool_bool(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  bool* val1 = reinterpret_cast<bool*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  bool* val2 = reinterpret_cast<bool*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 <= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Le_char_char(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int8_t* val1 = reinterpret_cast<int8_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int8_t* val2 = reinterpret_cast<int8_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 <= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Le_short_short(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int16_t* val1 = reinterpret_cast<int16_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int16_t* val2 = reinterpret_cast<int16_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 <= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Le_int_int(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int32_t* val1 = reinterpret_cast<int32_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int32_t* val2 = reinterpret_cast<int32_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 <= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Le_long_long(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  int64_t* val1 = reinterpret_cast<int64_t*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  int64_t* val2 = reinterpret_cast<int64_t*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 <= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Le_float_float(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  float* val1 = reinterpret_cast<float*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  float* val2 = reinterpret_cast<float*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 <= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Le_double_double(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  double* val1 = reinterpret_cast<double*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  double* val2 = reinterpret_cast<double*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 <= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Eq_StringValue_StringValue(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  StringValue* val1 = reinterpret_cast<StringValue*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  StringValue* val2 = reinterpret_cast<StringValue*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = val1->Eq(*val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ne_StringValue_StringValue(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  StringValue* val1 = reinterpret_cast<StringValue*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  StringValue* val2 = reinterpret_cast<StringValue*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = val1->Ne(*val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Gt_StringValue_StringValue(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  StringValue* val1 = reinterpret_cast<StringValue*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  StringValue* val2 = reinterpret_cast<StringValue*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = val1->Gt(*val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Lt_StringValue_StringValue(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  StringValue* val1 = reinterpret_cast<StringValue*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  StringValue* val2 = reinterpret_cast<StringValue*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = val1->Lt(*val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ge_StringValue_StringValue(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  StringValue* val1 = reinterpret_cast<StringValue*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  StringValue* val2 = reinterpret_cast<StringValue*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = val1->Ge(*val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Le_StringValue_StringValue(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  StringValue* val1 = reinterpret_cast<StringValue*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  StringValue* val2 = reinterpret_cast<StringValue*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = val1->Le(*val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Eq_TimestampValue_TimestampValue(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  TimestampValue* val1 = reinterpret_cast<TimestampValue*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  TimestampValue* val2 = reinterpret_cast<TimestampValue*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 == *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ne_TimestampValue_TimestampValue(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  TimestampValue* val1 = reinterpret_cast<TimestampValue*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  TimestampValue* val2 = reinterpret_cast<TimestampValue*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 != *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Gt_TimestampValue_TimestampValue(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  TimestampValue* val1 = reinterpret_cast<TimestampValue*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  TimestampValue* val2 = reinterpret_cast<TimestampValue*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 > *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Lt_TimestampValue_TimestampValue(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  TimestampValue* val1 = reinterpret_cast<TimestampValue*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  TimestampValue* val2 = reinterpret_cast<TimestampValue*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 < *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Ge_TimestampValue_TimestampValue(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  TimestampValue* val1 = reinterpret_cast<TimestampValue*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  TimestampValue* val2 = reinterpret_cast<TimestampValue*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 >= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Le_TimestampValue_TimestampValue(Expr* e, TupleRow* row) {
  Expr* op1 = e->children()[0];
  TimestampValue* val1 = reinterpret_cast<TimestampValue*>(op1->GetValue(row));
  Expr* op2 = e->children()[1];
  TimestampValue* val2 = reinterpret_cast<TimestampValue*>(op2->GetValue(row));
  if (val1 == NULL || val2 == NULL) return NULL;
  e->result_.bool_val = (*val1 <= *val2);
  return &e->result_.bool_val;
}

void* ComputeFunctions::Cast_bool_bool(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  bool* val = reinterpret_cast<bool*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bool_val = *val;
  return &e->result_.bool_val;
}

void* ComputeFunctions::Cast_char_bool(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int8_t* val = reinterpret_cast<int8_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bool_val = *val;
  return &e->result_.bool_val;
}

void* ComputeFunctions::Cast_short_bool(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int16_t* val = reinterpret_cast<int16_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bool_val = *val;
  return &e->result_.bool_val;
}

void* ComputeFunctions::Cast_int_bool(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int32_t* val = reinterpret_cast<int32_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bool_val = *val;
  return &e->result_.bool_val;
}

void* ComputeFunctions::Cast_long_bool(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int64_t* val = reinterpret_cast<int64_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bool_val = *val;
  return &e->result_.bool_val;
}

void* ComputeFunctions::Cast_float_bool(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  float* val = reinterpret_cast<float*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bool_val = *val;
  return &e->result_.bool_val;
}

void* ComputeFunctions::Cast_double_bool(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  double* val = reinterpret_cast<double*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bool_val = *val;
  return &e->result_.bool_val;
}

void* ComputeFunctions::Cast_bool_char(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  bool* val = reinterpret_cast<bool*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.tinyint_val = *val;
  return &e->result_.tinyint_val;
}

void* ComputeFunctions::Cast_char_char(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int8_t* val = reinterpret_cast<int8_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.tinyint_val = *val;
  return &e->result_.tinyint_val;
}

void* ComputeFunctions::Cast_short_char(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int16_t* val = reinterpret_cast<int16_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.tinyint_val = *val;
  return &e->result_.tinyint_val;
}

void* ComputeFunctions::Cast_int_char(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int32_t* val = reinterpret_cast<int32_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.tinyint_val = *val;
  return &e->result_.tinyint_val;
}

void* ComputeFunctions::Cast_long_char(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int64_t* val = reinterpret_cast<int64_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.tinyint_val = *val;
  return &e->result_.tinyint_val;
}

void* ComputeFunctions::Cast_float_char(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  float* val = reinterpret_cast<float*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.tinyint_val = *val;
  return &e->result_.tinyint_val;
}

void* ComputeFunctions::Cast_double_char(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  double* val = reinterpret_cast<double*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.tinyint_val = *val;
  return &e->result_.tinyint_val;
}

void* ComputeFunctions::Cast_bool_short(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  bool* val = reinterpret_cast<bool*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.smallint_val = *val;
  return &e->result_.smallint_val;
}

void* ComputeFunctions::Cast_char_short(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int8_t* val = reinterpret_cast<int8_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.smallint_val = *val;
  return &e->result_.smallint_val;
}

void* ComputeFunctions::Cast_short_short(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int16_t* val = reinterpret_cast<int16_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.smallint_val = *val;
  return &e->result_.smallint_val;
}

void* ComputeFunctions::Cast_int_short(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int32_t* val = reinterpret_cast<int32_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.smallint_val = *val;
  return &e->result_.smallint_val;
}

void* ComputeFunctions::Cast_long_short(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int64_t* val = reinterpret_cast<int64_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.smallint_val = *val;
  return &e->result_.smallint_val;
}

void* ComputeFunctions::Cast_float_short(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  float* val = reinterpret_cast<float*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.smallint_val = *val;
  return &e->result_.smallint_val;
}

void* ComputeFunctions::Cast_double_short(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  double* val = reinterpret_cast<double*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.smallint_val = *val;
  return &e->result_.smallint_val;
}

void* ComputeFunctions::Cast_bool_int(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  bool* val = reinterpret_cast<bool*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.int_val = *val;
  return &e->result_.int_val;
}

void* ComputeFunctions::Cast_char_int(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int8_t* val = reinterpret_cast<int8_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.int_val = *val;
  return &e->result_.int_val;
}

void* ComputeFunctions::Cast_short_int(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int16_t* val = reinterpret_cast<int16_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.int_val = *val;
  return &e->result_.int_val;
}

void* ComputeFunctions::Cast_int_int(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int32_t* val = reinterpret_cast<int32_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.int_val = *val;
  return &e->result_.int_val;
}

void* ComputeFunctions::Cast_long_int(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int64_t* val = reinterpret_cast<int64_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.int_val = *val;
  return &e->result_.int_val;
}

void* ComputeFunctions::Cast_float_int(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  float* val = reinterpret_cast<float*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.int_val = *val;
  return &e->result_.int_val;
}

void* ComputeFunctions::Cast_double_int(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  double* val = reinterpret_cast<double*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.int_val = *val;
  return &e->result_.int_val;
}

void* ComputeFunctions::Cast_bool_long(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  bool* val = reinterpret_cast<bool*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bigint_val = *val;
  return &e->result_.bigint_val;
}

void* ComputeFunctions::Cast_char_long(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int8_t* val = reinterpret_cast<int8_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bigint_val = *val;
  return &e->result_.bigint_val;
}

void* ComputeFunctions::Cast_short_long(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int16_t* val = reinterpret_cast<int16_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bigint_val = *val;
  return &e->result_.bigint_val;
}

void* ComputeFunctions::Cast_int_long(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int32_t* val = reinterpret_cast<int32_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bigint_val = *val;
  return &e->result_.bigint_val;
}

void* ComputeFunctions::Cast_long_long(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int64_t* val = reinterpret_cast<int64_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bigint_val = *val;
  return &e->result_.bigint_val;
}

void* ComputeFunctions::Cast_float_long(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  float* val = reinterpret_cast<float*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bigint_val = *val;
  return &e->result_.bigint_val;
}

void* ComputeFunctions::Cast_double_long(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  double* val = reinterpret_cast<double*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bigint_val = *val;
  return &e->result_.bigint_val;
}

void* ComputeFunctions::Cast_bool_float(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  bool* val = reinterpret_cast<bool*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.float_val = *val;
  return &e->result_.float_val;
}

void* ComputeFunctions::Cast_char_float(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int8_t* val = reinterpret_cast<int8_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.float_val = *val;
  return &e->result_.float_val;
}

void* ComputeFunctions::Cast_short_float(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int16_t* val = reinterpret_cast<int16_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.float_val = *val;
  return &e->result_.float_val;
}

void* ComputeFunctions::Cast_int_float(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int32_t* val = reinterpret_cast<int32_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.float_val = *val;
  return &e->result_.float_val;
}

void* ComputeFunctions::Cast_long_float(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int64_t* val = reinterpret_cast<int64_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.float_val = *val;
  return &e->result_.float_val;
}

void* ComputeFunctions::Cast_float_float(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  float* val = reinterpret_cast<float*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.float_val = *val;
  return &e->result_.float_val;
}

void* ComputeFunctions::Cast_double_float(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  double* val = reinterpret_cast<double*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.float_val = *val;
  return &e->result_.float_val;
}

void* ComputeFunctions::Cast_bool_double(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  bool* val = reinterpret_cast<bool*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.double_val = *val;
  return &e->result_.double_val;
}

void* ComputeFunctions::Cast_char_double(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int8_t* val = reinterpret_cast<int8_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.double_val = *val;
  return &e->result_.double_val;
}

void* ComputeFunctions::Cast_short_double(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int16_t* val = reinterpret_cast<int16_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.double_val = *val;
  return &e->result_.double_val;
}

void* ComputeFunctions::Cast_int_double(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int32_t* val = reinterpret_cast<int32_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.double_val = *val;
  return &e->result_.double_val;
}

void* ComputeFunctions::Cast_long_double(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int64_t* val = reinterpret_cast<int64_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.double_val = *val;
  return &e->result_.double_val;
}

void* ComputeFunctions::Cast_float_double(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  float* val = reinterpret_cast<float*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.double_val = *val;
  return &e->result_.double_val;
}

void* ComputeFunctions::Cast_double_double(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  double* val = reinterpret_cast<double*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.double_val = *val;
  return &e->result_.double_val;
}

void* ComputeFunctions::Cast_StringValue_char(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  StringValue* val = reinterpret_cast<StringValue*>(op->GetValue(row));
  if (val == NULL) return NULL;
  StringParser::ParseResult result;
  e->result_.tinyint_val =       StringParser::StringToInt<int8_t>(val->ptr, val->len, &result);
  if (UNLIKELY(result != StringParser::PARSE_SUCCESS)) return NULL;
  return &e->result_.tinyint_val;
}

void* ComputeFunctions::Cast_StringValue_short(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  StringValue* val = reinterpret_cast<StringValue*>(op->GetValue(row));
  if (val == NULL) return NULL;
  StringParser::ParseResult result;
  e->result_.smallint_val =       StringParser::StringToInt<int16_t>(val->ptr, val->len, &result);
  if (UNLIKELY(result != StringParser::PARSE_SUCCESS)) return NULL;
  return &e->result_.smallint_val;
}

void* ComputeFunctions::Cast_StringValue_int(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  StringValue* val = reinterpret_cast<StringValue*>(op->GetValue(row));
  if (val == NULL) return NULL;
  StringParser::ParseResult result;
  e->result_.int_val =       StringParser::StringToInt<int32_t>(val->ptr, val->len, &result);
  if (UNLIKELY(result != StringParser::PARSE_SUCCESS)) return NULL;
  return &e->result_.int_val;
}

void* ComputeFunctions::Cast_StringValue_long(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  StringValue* val = reinterpret_cast<StringValue*>(op->GetValue(row));
  if (val == NULL) return NULL;
  StringParser::ParseResult result;
  e->result_.bigint_val =       StringParser::StringToInt<int64_t>(val->ptr, val->len, &result);
  if (UNLIKELY(result != StringParser::PARSE_SUCCESS)) return NULL;
  return &e->result_.bigint_val;
}

void* ComputeFunctions::Cast_StringValue_float(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  StringValue* val = reinterpret_cast<StringValue*>(op->GetValue(row));
  if (val == NULL) return NULL;
  StringParser::ParseResult result;
  e->result_.float_val =       StringParser::StringToFloat<float>(val->ptr, val->len, &result);
  if (UNLIKELY(result != StringParser::PARSE_SUCCESS)) return NULL;
  return &e->result_.float_val;
}

void* ComputeFunctions::Cast_StringValue_double(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  StringValue* val = reinterpret_cast<StringValue*>(op->GetValue(row));
  if (val == NULL) return NULL;
  StringParser::ParseResult result;
  e->result_.double_val =       StringParser::StringToFloat<double>(val->ptr, val->len, &result);
  if (UNLIKELY(result != StringParser::PARSE_SUCCESS)) return NULL;
  return &e->result_.double_val;
}

void* ComputeFunctions::Cast_bool_StringValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  bool* val = reinterpret_cast<bool*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.SetStringVal(lexical_cast<string>(*val));
  return &e->result_.string_val;
}

void* ComputeFunctions::Cast_short_StringValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int16_t* val = reinterpret_cast<int16_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.SetStringVal(lexical_cast<string>(*val));
  return &e->result_.string_val;
}

void* ComputeFunctions::Cast_int_StringValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int32_t* val = reinterpret_cast<int32_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.SetStringVal(lexical_cast<string>(*val));
  return &e->result_.string_val;
}

void* ComputeFunctions::Cast_long_StringValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int64_t* val = reinterpret_cast<int64_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.SetStringVal(lexical_cast<string>(*val));
  return &e->result_.string_val;
}

void* ComputeFunctions::Cast_float_StringValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  float* val = reinterpret_cast<float*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.SetStringVal(lexical_cast<string>(*val));
  return &e->result_.string_val;
}

void* ComputeFunctions::Cast_double_StringValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  double* val = reinterpret_cast<double*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.SetStringVal(lexical_cast<string>(*val));
  return &e->result_.string_val;
}

void* ComputeFunctions::Cast_char_StringValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int8_t* val = reinterpret_cast<int8_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  int64_t tmp_val = *val;
  e->result_.SetStringVal(lexical_cast<string>(tmp_val));
  return &e->result_.string_val;
}

void* ComputeFunctions::Cast_TimestampValue_bool(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  TimestampValue* val = reinterpret_cast<TimestampValue*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bool_val = *val;
  return &e->result_.bool_val;
}

void* ComputeFunctions::Cast_TimestampValue_char(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  TimestampValue* val = reinterpret_cast<TimestampValue*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.tinyint_val = *val;
  return &e->result_.tinyint_val;
}

void* ComputeFunctions::Cast_TimestampValue_short(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  TimestampValue* val = reinterpret_cast<TimestampValue*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.smallint_val = *val;
  return &e->result_.smallint_val;
}

void* ComputeFunctions::Cast_TimestampValue_int(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  TimestampValue* val = reinterpret_cast<TimestampValue*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.int_val = *val;
  return &e->result_.int_val;
}

void* ComputeFunctions::Cast_TimestampValue_long(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  TimestampValue* val = reinterpret_cast<TimestampValue*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.bigint_val = *val;
  return &e->result_.bigint_val;
}

void* ComputeFunctions::Cast_TimestampValue_float(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  TimestampValue* val = reinterpret_cast<TimestampValue*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.float_val = *val;
  return &e->result_.float_val;
}

void* ComputeFunctions::Cast_TimestampValue_double(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  TimestampValue* val = reinterpret_cast<TimestampValue*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.double_val = *val;
  return &e->result_.double_val;
}

void* ComputeFunctions::Cast_TimestampValue_StringValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  TimestampValue* val = reinterpret_cast<TimestampValue*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.SetStringVal(lexical_cast<string>(*val));
  return &e->result_.string_val;
}

void* ComputeFunctions::Cast_StringValue_TimestampValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  StringValue* val = reinterpret_cast<StringValue*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.timestamp_val = TimestampValue(val->ptr, val->len);
  return &e->result_.timestamp_val;
}

void* ComputeFunctions::Cast_bool_TimestampValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  bool* val = reinterpret_cast<bool*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.timestamp_val = *val;
  return &e->result_.timestamp_val;
}

void* ComputeFunctions::Cast_char_TimestampValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int8_t* val = reinterpret_cast<int8_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.timestamp_val = *val;
  return &e->result_.timestamp_val;
}

void* ComputeFunctions::Cast_short_TimestampValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int16_t* val = reinterpret_cast<int16_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.timestamp_val = *val;
  return &e->result_.timestamp_val;
}

void* ComputeFunctions::Cast_int_TimestampValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int32_t* val = reinterpret_cast<int32_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.timestamp_val = *val;
  return &e->result_.timestamp_val;
}

void* ComputeFunctions::Cast_long_TimestampValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  int64_t* val = reinterpret_cast<int64_t*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.timestamp_val = *val;
  return &e->result_.timestamp_val;
}

void* ComputeFunctions::Cast_float_TimestampValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  float* val = reinterpret_cast<float*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.timestamp_val = *val;
  return &e->result_.timestamp_val;
}

void* ComputeFunctions::Cast_double_TimestampValue(Expr* e, TupleRow* row) {
  Expr* op = e->children()[0];
  double* val = reinterpret_cast<double*>(op->GetValue(row));
  if (val == NULL) return NULL;
  e->result_.timestamp_val = *val;
  return &e->result_.timestamp_val;
}

void* ComputeFunctions::Case_bool(Expr* e, TupleRow* row) {
  CaseExpr* expr = static_cast<CaseExpr*>(e);
  int num_children = e->GetNumChildren();
  int loop_end = (expr->has_else_expr()) ? num_children - 1 : num_children;
  // Make sure we set the right compute function.
  DCHECK_EQ(expr->has_case_expr(), true);
  // Need at least case, when and then expr, and optionally an else.
  DCHECK_GE(num_children, (expr->has_else_expr()) ? 4 : 3);
  // All case and when exprs return the same type (we guaranteed that during analysis).
  void* case_val = e->children()[0]->GetValue(row);
  if (case_val == NULL) {
    if (expr->has_else_expr()) {
      // Return else value.
      return e->children()[num_children - 1]->GetValue(row);
    } else {
      return NULL;
    }
  }
  for (int i = 1; i < loop_end; i += 2) {
    bool* when_val =
        reinterpret_cast<bool*>(e->children()[i]->GetValue(row));
    if (when_val == NULL) continue;
    if (*reinterpret_cast<bool*>(case_val) == *when_val) {
      // Return then value.
      return e->children()[i + 1]->GetValue(row);
    }
  }
  if (expr->has_else_expr()) {
    // Return else value.
    return e->children()[num_children - 1]->GetValue(row);
  }
  return NULL;
}

void* ComputeFunctions::Case_char(Expr* e, TupleRow* row) {
  CaseExpr* expr = static_cast<CaseExpr*>(e);
  int num_children = e->GetNumChildren();
  int loop_end = (expr->has_else_expr()) ? num_children - 1 : num_children;
  // Make sure we set the right compute function.
  DCHECK_EQ(expr->has_case_expr(), true);
  // Need at least case, when and then expr, and optionally an else.
  DCHECK_GE(num_children, (expr->has_else_expr()) ? 4 : 3);
  // All case and when exprs return the same type (we guaranteed that during analysis).
  void* case_val = e->children()[0]->GetValue(row);
  if (case_val == NULL) {
    if (expr->has_else_expr()) {
      // Return else value.
      return e->children()[num_children - 1]->GetValue(row);
    } else {
      return NULL;
    }
  }
  for (int i = 1; i < loop_end; i += 2) {
    int8_t* when_val =
        reinterpret_cast<int8_t*>(e->children()[i]->GetValue(row));
    if (when_val == NULL) continue;
    if (*reinterpret_cast<int8_t*>(case_val) == *when_val) {
      // Return then value.
      return e->children()[i + 1]->GetValue(row);
    }
  }
  if (expr->has_else_expr()) {
    // Return else value.
    return e->children()[num_children - 1]->GetValue(row);
  }
  return NULL;
}

void* ComputeFunctions::Case_short(Expr* e, TupleRow* row) {
  CaseExpr* expr = static_cast<CaseExpr*>(e);
  int num_children = e->GetNumChildren();
  int loop_end = (expr->has_else_expr()) ? num_children - 1 : num_children;
  // Make sure we set the right compute function.
  DCHECK_EQ(expr->has_case_expr(), true);
  // Need at least case, when and then expr, and optionally an else.
  DCHECK_GE(num_children, (expr->has_else_expr()) ? 4 : 3);
  // All case and when exprs return the same type (we guaranteed that during analysis).
  void* case_val = e->children()[0]->GetValue(row);
  if (case_val == NULL) {
    if (expr->has_else_expr()) {
      // Return else value.
      return e->children()[num_children - 1]->GetValue(row);
    } else {
      return NULL;
    }
  }
  for (int i = 1; i < loop_end; i += 2) {
    int16_t* when_val =
        reinterpret_cast<int16_t*>(e->children()[i]->GetValue(row));
    if (when_val == NULL) continue;
    if (*reinterpret_cast<int16_t*>(case_val) == *when_val) {
      // Return then value.
      return e->children()[i + 1]->GetValue(row);
    }
  }
  if (expr->has_else_expr()) {
    // Return else value.
    return e->children()[num_children - 1]->GetValue(row);
  }
  return NULL;
}

void* ComputeFunctions::Case_int(Expr* e, TupleRow* row) {
  CaseExpr* expr = static_cast<CaseExpr*>(e);
  int num_children = e->GetNumChildren();
  int loop_end = (expr->has_else_expr()) ? num_children - 1 : num_children;
  // Make sure we set the right compute function.
  DCHECK_EQ(expr->has_case_expr(), true);
  // Need at least case, when and then expr, and optionally an else.
  DCHECK_GE(num_children, (expr->has_else_expr()) ? 4 : 3);
  // All case and when exprs return the same type (we guaranteed that during analysis).
  void* case_val = e->children()[0]->GetValue(row);
  if (case_val == NULL) {
    if (expr->has_else_expr()) {
      // Return else value.
      return e->children()[num_children - 1]->GetValue(row);
    } else {
      return NULL;
    }
  }
  for (int i = 1; i < loop_end; i += 2) {
    int32_t* when_val =
        reinterpret_cast<int32_t*>(e->children()[i]->GetValue(row));
    if (when_val == NULL) continue;
    if (*reinterpret_cast<int32_t*>(case_val) == *when_val) {
      // Return then value.
      return e->children()[i + 1]->GetValue(row);
    }
  }
  if (expr->has_else_expr()) {
    // Return else value.
    return e->children()[num_children - 1]->GetValue(row);
  }
  return NULL;
}

void* ComputeFunctions::Case_long(Expr* e, TupleRow* row) {
  CaseExpr* expr = static_cast<CaseExpr*>(e);
  int num_children = e->GetNumChildren();
  int loop_end = (expr->has_else_expr()) ? num_children - 1 : num_children;
  // Make sure we set the right compute function.
  DCHECK_EQ(expr->has_case_expr(), true);
  // Need at least case, when and then expr, and optionally an else.
  DCHECK_GE(num_children, (expr->has_else_expr()) ? 4 : 3);
  // All case and when exprs return the same type (we guaranteed that during analysis).
  void* case_val = e->children()[0]->GetValue(row);
  if (case_val == NULL) {
    if (expr->has_else_expr()) {
      // Return else value.
      return e->children()[num_children - 1]->GetValue(row);
    } else {
      return NULL;
    }
  }
  for (int i = 1; i < loop_end; i += 2) {
    int64_t* when_val =
        reinterpret_cast<int64_t*>(e->children()[i]->GetValue(row));
    if (when_val == NULL) continue;
    if (*reinterpret_cast<int64_t*>(case_val) == *when_val) {
      // Return then value.
      return e->children()[i + 1]->GetValue(row);
    }
  }
  if (expr->has_else_expr()) {
    // Return else value.
    return e->children()[num_children - 1]->GetValue(row);
  }
  return NULL;
}

void* ComputeFunctions::Case_float(Expr* e, TupleRow* row) {
  CaseExpr* expr = static_cast<CaseExpr*>(e);
  int num_children = e->GetNumChildren();
  int loop_end = (expr->has_else_expr()) ? num_children - 1 : num_children;
  // Make sure we set the right compute function.
  DCHECK_EQ(expr->has_case_expr(), true);
  // Need at least case, when and then expr, and optionally an else.
  DCHECK_GE(num_children, (expr->has_else_expr()) ? 4 : 3);
  // All case and when exprs return the same type (we guaranteed that during analysis).
  void* case_val = e->children()[0]->GetValue(row);
  if (case_val == NULL) {
    if (expr->has_else_expr()) {
      // Return else value.
      return e->children()[num_children - 1]->GetValue(row);
    } else {
      return NULL;
    }
  }
  for (int i = 1; i < loop_end; i += 2) {
    float* when_val =
        reinterpret_cast<float*>(e->children()[i]->GetValue(row));
    if (when_val == NULL) continue;
    if (*reinterpret_cast<float*>(case_val) == *when_val) {
      // Return then value.
      return e->children()[i + 1]->GetValue(row);
    }
  }
  if (expr->has_else_expr()) {
    // Return else value.
    return e->children()[num_children - 1]->GetValue(row);
  }
  return NULL;
}

void* ComputeFunctions::Case_double(Expr* e, TupleRow* row) {
  CaseExpr* expr = static_cast<CaseExpr*>(e);
  int num_children = e->GetNumChildren();
  int loop_end = (expr->has_else_expr()) ? num_children - 1 : num_children;
  // Make sure we set the right compute function.
  DCHECK_EQ(expr->has_case_expr(), true);
  // Need at least case, when and then expr, and optionally an else.
  DCHECK_GE(num_children, (expr->has_else_expr()) ? 4 : 3);
  // All case and when exprs return the same type (we guaranteed that during analysis).
  void* case_val = e->children()[0]->GetValue(row);
  if (case_val == NULL) {
    if (expr->has_else_expr()) {
      // Return else value.
      return e->children()[num_children - 1]->GetValue(row);
    } else {
      return NULL;
    }
  }
  for (int i = 1; i < loop_end; i += 2) {
    double* when_val =
        reinterpret_cast<double*>(e->children()[i]->GetValue(row));
    if (when_val == NULL) continue;
    if (*reinterpret_cast<double*>(case_val) == *when_val) {
      // Return then value.
      return e->children()[i + 1]->GetValue(row);
    }
  }
  if (expr->has_else_expr()) {
    // Return else value.
    return e->children()[num_children - 1]->GetValue(row);
  }
  return NULL;
}

void* ComputeFunctions::Case_StringValue(Expr* e, TupleRow* row) {
  CaseExpr* expr = static_cast<CaseExpr*>(e);
  int num_children = e->GetNumChildren();
  int loop_end = (expr->has_else_expr()) ? num_children - 1 : num_children;
  // Make sure we set the right compute function.
  DCHECK_EQ(expr->has_case_expr(), true);
  // Need at least case, when and then expr, and optionally an else.
  DCHECK_GE(num_children, (expr->has_else_expr()) ? 4 : 3);
  // All case and when exprs return the same type (we guaranteed that during analysis).
  void* case_val = e->children()[0]->GetValue(row);
  if (case_val == NULL) {
    if (expr->has_else_expr()) {
      // Return else value.
      return e->children()[num_children - 1]->GetValue(row);
    } else {
      return NULL;
    }
  }
  for (int i = 1; i < loop_end; i += 2) {
    StringValue* when_val =
        reinterpret_cast<StringValue*>(e->children()[i]->GetValue(row));
    if (when_val == NULL) continue;
    if (*reinterpret_cast<StringValue*>(case_val) == *when_val) {
      // Return then value.
      return e->children()[i + 1]->GetValue(row);
    }
  }
  if (expr->has_else_expr()) {
    // Return else value.
    return e->children()[num_children - 1]->GetValue(row);
  }
  return NULL;
}

void* ComputeFunctions::Case_TimestampValue(Expr* e, TupleRow* row) {
  CaseExpr* expr = static_cast<CaseExpr*>(e);
  int num_children = e->GetNumChildren();
  int loop_end = (expr->has_else_expr()) ? num_children - 1 : num_children;
  // Make sure we set the right compute function.
  DCHECK_EQ(expr->has_case_expr(), true);
  // Need at least case, when and then expr, and optionally an else.
  DCHECK_GE(num_children, (expr->has_else_expr()) ? 4 : 3);
  // All case and when exprs return the same type (we guaranteed that during analysis).
  void* case_val = e->children()[0]->GetValue(row);
  if (case_val == NULL) {
    if (expr->has_else_expr()) {
      // Return else value.
      return e->children()[num_children - 1]->GetValue(row);
    } else {
      return NULL;
    }
  }
  for (int i = 1; i < loop_end; i += 2) {
    TimestampValue* when_val =
        reinterpret_cast<TimestampValue*>(e->children()[i]->GetValue(row));
    if (when_val == NULL) continue;
    if (*reinterpret_cast<TimestampValue*>(case_val) == *when_val) {
      // Return then value.
      return e->children()[i + 1]->GetValue(row);
    }
  }
  if (expr->has_else_expr()) {
    // Return else value.
    return e->children()[num_children - 1]->GetValue(row);
  }
  return NULL;
}

}
