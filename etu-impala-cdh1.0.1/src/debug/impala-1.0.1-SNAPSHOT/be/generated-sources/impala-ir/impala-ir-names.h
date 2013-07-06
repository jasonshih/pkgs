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
// To add new functions, see be/src/codegen/gen_ir_descriptions.py.

#ifndef IMPALA_IR_FUNCTION_NAMES_H
#define IMPALA_IR_FUNCTION_NAMES_H

#include "impala-ir/impala-ir-functions.h"

namespace impala {

static struct {
  std::string fn_name; 
  IRFunction::Type fn; 
} FN_MAPPINGS[] = {
  { "ProcessRowBatchWithGrouping", IRFunction::AGG_NODE_PROCESS_ROW_BATCH_WITH_GROUPING },
  { "ProcessRowBatchNoGrouping", IRFunction::AGG_NODE_PROCESS_ROW_BATCH_NO_GROUPING },
  { "IrExprGetValue", IRFunction::EXPR_GET_VALUE },
  { "IrCrcHash", IRFunction::HASH_CRC },
  { "IrFvnHash", IRFunction::HASH_FVN },
  { "ProcessBuildBatch", IRFunction::HASH_JOIN_PROCESS_BUILD_BATCH },
  { "ProcessProbeBatch", IRFunction::HASH_JOIN_PROCESS_PROBE_BATCH },
  { "WriteAlignedTuples", IRFunction::HDFS_SCANNER_WRITE_ALIGNED_TUPLES },
  { "StringValueEQ", IRFunction::STRING_VALUE_EQ },
  { "StringValueNE", IRFunction::STRING_VALUE_NE },
  { "StringValueGE", IRFunction::STRING_VALUE_GE },
  { "StringValueGT", IRFunction::STRING_VALUE_GT },
  { "StringValueLT", IRFunction::STRING_VALUE_LT },
  { "StringValueLE", IRFunction::STRING_VALUE_LE },
  { "IrStringToBool", IRFunction::STRING_TO_BOOL },
  { "IrStringToInt8", IRFunction::STRING_TO_INT8 },
  { "IrStringToInt16", IRFunction::STRING_TO_INT16 },
  { "IrStringToInt32", IRFunction::STRING_TO_INT32 },
  { "IrStringToInt64", IRFunction::STRING_TO_INT64 },
  { "IrStringToFloat", IRFunction::STRING_TO_FLOAT },
  { "IrStringToDouble", IRFunction::STRING_TO_DOUBLE },
  { "IrIsNullString", IRFunction::IS_NULL_STRING },
  { "IrGenericIsNullString", IRFunction::GENERIC_IS_NULL_STRING },
};

}

#endif
