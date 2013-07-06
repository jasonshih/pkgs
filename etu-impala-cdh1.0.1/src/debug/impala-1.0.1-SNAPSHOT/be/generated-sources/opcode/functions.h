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

// This is a generated file, DO NOT EDIT IT.
// To add new functions, see impala/common/function-registry/gen_opcodes.py

#ifndef IMPALA_OPCODE_FUNCTIONS_H
#define IMPALA_OPCODE_FUNCTIONS_H

namespace impala {
class Expr;
class OpcodeRegistry;
class TupleRow;

class ComputeFunctions {
 public:
  static void* Add_long_long(Expr* e, TupleRow* row);
  static void* Add_double_double(Expr* e, TupleRow* row);
  static void* Subtract_long_long(Expr* e, TupleRow* row);
  static void* Subtract_double_double(Expr* e, TupleRow* row);
  static void* Multiply_long_long(Expr* e, TupleRow* row);
  static void* Multiply_double_double(Expr* e, TupleRow* row);
  static void* Divide_double_double(Expr* e, TupleRow* row);
  static void* Int_Divide_char_char(Expr* e, TupleRow* row);
  static void* Int_Divide_short_short(Expr* e, TupleRow* row);
  static void* Int_Divide_int_int(Expr* e, TupleRow* row);
  static void* Int_Divide_long_long(Expr* e, TupleRow* row);
  static void* Mod_char_char(Expr* e, TupleRow* row);
  static void* Mod_short_short(Expr* e, TupleRow* row);
  static void* Mod_int_int(Expr* e, TupleRow* row);
  static void* Mod_long_long(Expr* e, TupleRow* row);
  static void* BitAnd_char_char(Expr* e, TupleRow* row);
  static void* BitAnd_short_short(Expr* e, TupleRow* row);
  static void* BitAnd_int_int(Expr* e, TupleRow* row);
  static void* BitAnd_long_long(Expr* e, TupleRow* row);
  static void* BitXor_char_char(Expr* e, TupleRow* row);
  static void* BitXor_short_short(Expr* e, TupleRow* row);
  static void* BitXor_int_int(Expr* e, TupleRow* row);
  static void* BitXor_long_long(Expr* e, TupleRow* row);
  static void* BitOr_char_char(Expr* e, TupleRow* row);
  static void* BitOr_short_short(Expr* e, TupleRow* row);
  static void* BitOr_int_int(Expr* e, TupleRow* row);
  static void* BitOr_long_long(Expr* e, TupleRow* row);
  static void* BitNot_char(Expr* e, TupleRow* row);
  static void* BitNot_short(Expr* e, TupleRow* row);
  static void* BitNot_int(Expr* e, TupleRow* row);
  static void* BitNot_long(Expr* e, TupleRow* row);
  static void* Eq_bool_bool(Expr* e, TupleRow* row);
  static void* Eq_char_char(Expr* e, TupleRow* row);
  static void* Eq_short_short(Expr* e, TupleRow* row);
  static void* Eq_int_int(Expr* e, TupleRow* row);
  static void* Eq_long_long(Expr* e, TupleRow* row);
  static void* Eq_float_float(Expr* e, TupleRow* row);
  static void* Eq_double_double(Expr* e, TupleRow* row);
  static void* Ne_bool_bool(Expr* e, TupleRow* row);
  static void* Ne_char_char(Expr* e, TupleRow* row);
  static void* Ne_short_short(Expr* e, TupleRow* row);
  static void* Ne_int_int(Expr* e, TupleRow* row);
  static void* Ne_long_long(Expr* e, TupleRow* row);
  static void* Ne_float_float(Expr* e, TupleRow* row);
  static void* Ne_double_double(Expr* e, TupleRow* row);
  static void* Gt_bool_bool(Expr* e, TupleRow* row);
  static void* Gt_char_char(Expr* e, TupleRow* row);
  static void* Gt_short_short(Expr* e, TupleRow* row);
  static void* Gt_int_int(Expr* e, TupleRow* row);
  static void* Gt_long_long(Expr* e, TupleRow* row);
  static void* Gt_float_float(Expr* e, TupleRow* row);
  static void* Gt_double_double(Expr* e, TupleRow* row);
  static void* Lt_bool_bool(Expr* e, TupleRow* row);
  static void* Lt_char_char(Expr* e, TupleRow* row);
  static void* Lt_short_short(Expr* e, TupleRow* row);
  static void* Lt_int_int(Expr* e, TupleRow* row);
  static void* Lt_long_long(Expr* e, TupleRow* row);
  static void* Lt_float_float(Expr* e, TupleRow* row);
  static void* Lt_double_double(Expr* e, TupleRow* row);
  static void* Ge_bool_bool(Expr* e, TupleRow* row);
  static void* Ge_char_char(Expr* e, TupleRow* row);
  static void* Ge_short_short(Expr* e, TupleRow* row);
  static void* Ge_int_int(Expr* e, TupleRow* row);
  static void* Ge_long_long(Expr* e, TupleRow* row);
  static void* Ge_float_float(Expr* e, TupleRow* row);
  static void* Ge_double_double(Expr* e, TupleRow* row);
  static void* Le_bool_bool(Expr* e, TupleRow* row);
  static void* Le_char_char(Expr* e, TupleRow* row);
  static void* Le_short_short(Expr* e, TupleRow* row);
  static void* Le_int_int(Expr* e, TupleRow* row);
  static void* Le_long_long(Expr* e, TupleRow* row);
  static void* Le_float_float(Expr* e, TupleRow* row);
  static void* Le_double_double(Expr* e, TupleRow* row);
  static void* Eq_StringValue_StringValue(Expr* e, TupleRow* row);
  static void* Ne_StringValue_StringValue(Expr* e, TupleRow* row);
  static void* Gt_StringValue_StringValue(Expr* e, TupleRow* row);
  static void* Lt_StringValue_StringValue(Expr* e, TupleRow* row);
  static void* Ge_StringValue_StringValue(Expr* e, TupleRow* row);
  static void* Le_StringValue_StringValue(Expr* e, TupleRow* row);
  static void* Eq_TimestampValue_TimestampValue(Expr* e, TupleRow* row);
  static void* Ne_TimestampValue_TimestampValue(Expr* e, TupleRow* row);
  static void* Gt_TimestampValue_TimestampValue(Expr* e, TupleRow* row);
  static void* Lt_TimestampValue_TimestampValue(Expr* e, TupleRow* row);
  static void* Ge_TimestampValue_TimestampValue(Expr* e, TupleRow* row);
  static void* Le_TimestampValue_TimestampValue(Expr* e, TupleRow* row);
  static void* Cast_bool_bool(Expr* e, TupleRow* row);
  static void* Cast_char_bool(Expr* e, TupleRow* row);
  static void* Cast_short_bool(Expr* e, TupleRow* row);
  static void* Cast_int_bool(Expr* e, TupleRow* row);
  static void* Cast_long_bool(Expr* e, TupleRow* row);
  static void* Cast_float_bool(Expr* e, TupleRow* row);
  static void* Cast_double_bool(Expr* e, TupleRow* row);
  static void* Cast_bool_char(Expr* e, TupleRow* row);
  static void* Cast_char_char(Expr* e, TupleRow* row);
  static void* Cast_short_char(Expr* e, TupleRow* row);
  static void* Cast_int_char(Expr* e, TupleRow* row);
  static void* Cast_long_char(Expr* e, TupleRow* row);
  static void* Cast_float_char(Expr* e, TupleRow* row);
  static void* Cast_double_char(Expr* e, TupleRow* row);
  static void* Cast_bool_short(Expr* e, TupleRow* row);
  static void* Cast_char_short(Expr* e, TupleRow* row);
  static void* Cast_short_short(Expr* e, TupleRow* row);
  static void* Cast_int_short(Expr* e, TupleRow* row);
  static void* Cast_long_short(Expr* e, TupleRow* row);
  static void* Cast_float_short(Expr* e, TupleRow* row);
  static void* Cast_double_short(Expr* e, TupleRow* row);
  static void* Cast_bool_int(Expr* e, TupleRow* row);
  static void* Cast_char_int(Expr* e, TupleRow* row);
  static void* Cast_short_int(Expr* e, TupleRow* row);
  static void* Cast_int_int(Expr* e, TupleRow* row);
  static void* Cast_long_int(Expr* e, TupleRow* row);
  static void* Cast_float_int(Expr* e, TupleRow* row);
  static void* Cast_double_int(Expr* e, TupleRow* row);
  static void* Cast_bool_long(Expr* e, TupleRow* row);
  static void* Cast_char_long(Expr* e, TupleRow* row);
  static void* Cast_short_long(Expr* e, TupleRow* row);
  static void* Cast_int_long(Expr* e, TupleRow* row);
  static void* Cast_long_long(Expr* e, TupleRow* row);
  static void* Cast_float_long(Expr* e, TupleRow* row);
  static void* Cast_double_long(Expr* e, TupleRow* row);
  static void* Cast_bool_float(Expr* e, TupleRow* row);
  static void* Cast_char_float(Expr* e, TupleRow* row);
  static void* Cast_short_float(Expr* e, TupleRow* row);
  static void* Cast_int_float(Expr* e, TupleRow* row);
  static void* Cast_long_float(Expr* e, TupleRow* row);
  static void* Cast_float_float(Expr* e, TupleRow* row);
  static void* Cast_double_float(Expr* e, TupleRow* row);
  static void* Cast_bool_double(Expr* e, TupleRow* row);
  static void* Cast_char_double(Expr* e, TupleRow* row);
  static void* Cast_short_double(Expr* e, TupleRow* row);
  static void* Cast_int_double(Expr* e, TupleRow* row);
  static void* Cast_long_double(Expr* e, TupleRow* row);
  static void* Cast_float_double(Expr* e, TupleRow* row);
  static void* Cast_double_double(Expr* e, TupleRow* row);
  static void* Cast_StringValue_char(Expr* e, TupleRow* row);
  static void* Cast_StringValue_short(Expr* e, TupleRow* row);
  static void* Cast_StringValue_int(Expr* e, TupleRow* row);
  static void* Cast_StringValue_long(Expr* e, TupleRow* row);
  static void* Cast_StringValue_float(Expr* e, TupleRow* row);
  static void* Cast_StringValue_double(Expr* e, TupleRow* row);
  static void* Cast_bool_StringValue(Expr* e, TupleRow* row);
  static void* Cast_short_StringValue(Expr* e, TupleRow* row);
  static void* Cast_int_StringValue(Expr* e, TupleRow* row);
  static void* Cast_long_StringValue(Expr* e, TupleRow* row);
  static void* Cast_float_StringValue(Expr* e, TupleRow* row);
  static void* Cast_double_StringValue(Expr* e, TupleRow* row);
  static void* Cast_char_StringValue(Expr* e, TupleRow* row);
  static void* Cast_TimestampValue_bool(Expr* e, TupleRow* row);
  static void* Cast_TimestampValue_char(Expr* e, TupleRow* row);
  static void* Cast_TimestampValue_short(Expr* e, TupleRow* row);
  static void* Cast_TimestampValue_int(Expr* e, TupleRow* row);
  static void* Cast_TimestampValue_long(Expr* e, TupleRow* row);
  static void* Cast_TimestampValue_float(Expr* e, TupleRow* row);
  static void* Cast_TimestampValue_double(Expr* e, TupleRow* row);
  static void* Cast_TimestampValue_StringValue(Expr* e, TupleRow* row);
  static void* Cast_StringValue_TimestampValue(Expr* e, TupleRow* row);
  static void* Cast_bool_TimestampValue(Expr* e, TupleRow* row);
  static void* Cast_char_TimestampValue(Expr* e, TupleRow* row);
  static void* Cast_short_TimestampValue(Expr* e, TupleRow* row);
  static void* Cast_int_TimestampValue(Expr* e, TupleRow* row);
  static void* Cast_long_TimestampValue(Expr* e, TupleRow* row);
  static void* Cast_float_TimestampValue(Expr* e, TupleRow* row);
  static void* Cast_double_TimestampValue(Expr* e, TupleRow* row);
  static void* Case_bool(Expr* e, TupleRow* row);
  static void* Case_char(Expr* e, TupleRow* row);
  static void* Case_short(Expr* e, TupleRow* row);
  static void* Case_int(Expr* e, TupleRow* row);
  static void* Case_long(Expr* e, TupleRow* row);
  static void* Case_float(Expr* e, TupleRow* row);
  static void* Case_double(Expr* e, TupleRow* row);
  static void* Case_StringValue(Expr* e, TupleRow* row);
  static void* Case_TimestampValue(Expr* e, TupleRow* row);
};

}

#endif
