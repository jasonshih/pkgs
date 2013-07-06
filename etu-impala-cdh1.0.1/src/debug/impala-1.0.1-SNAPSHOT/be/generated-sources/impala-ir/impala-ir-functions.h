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

#ifndef IMPALA_IR_FUNCTIONS_H
#define IMPALA_IR_FUNCTIONS_H

namespace impala {

class IRFunction {
 public:
  enum Type {
    FN_START = 0,
    AGG_NODE_PROCESS_ROW_BATCH_WITH_GROUPING = 0,
    AGG_NODE_PROCESS_ROW_BATCH_NO_GROUPING = 1,
    EXPR_GET_VALUE = 2,
    HASH_CRC = 3,
    HASH_FVN = 4,
    HASH_JOIN_PROCESS_BUILD_BATCH = 5,
    HASH_JOIN_PROCESS_PROBE_BATCH = 6,
    HDFS_SCANNER_WRITE_ALIGNED_TUPLES = 7,
    STRING_VALUE_EQ = 8,
    STRING_VALUE_NE = 9,
    STRING_VALUE_GE = 10,
    STRING_VALUE_GT = 11,
    STRING_VALUE_LT = 12,
    STRING_VALUE_LE = 13,
    STRING_TO_BOOL = 14,
    STRING_TO_INT8 = 15,
    STRING_TO_INT16 = 16,
    STRING_TO_INT32 = 17,
    STRING_TO_INT64 = 18,
    STRING_TO_FLOAT = 19,
    STRING_TO_DOUBLE = 20,
    IS_NULL_STRING = 21,
    GENERIC_IS_NULL_STRING = 22,
    FN_END = 23
  };
};

}

#endif
