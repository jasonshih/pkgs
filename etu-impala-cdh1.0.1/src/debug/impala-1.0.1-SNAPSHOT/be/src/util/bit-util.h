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


#ifndef IMPALA_BIT_UTIL_H
#define IMPALA_BIT_UTIL_H

#include "common/compiler-util.h"
#include "util/cpu-info.h"

namespace impala {

// Utility class to do standard bit tricks
// TODO: is this in boost or something else like that?
class BitUtil {
 public:
  // Returns the ceil of value/divisor
  static inline int Ceil(int value, int divisor) {
    return value / divisor + (value % divisor != 0);
  }

  // Non hw accelerated pop count.
  // TODO: we don't use this in any perf sensitive code paths currently.  There
  // might be a much faster way to implement this.
  static inline int PopcountNoHw(uint64_t x) {
    int count = 0;
    for (; x != 0; ++count) x &= x-1;
    return count;
  }

  // Returns the number of set bits in x
  static inline int Popcount(uint64_t x) {
    if (LIKELY(CpuInfo::IsSupported(CpuInfo::POPCNT))) {
      return __builtin_popcountl(x);
    } else {
      return PopcountNoHw(x);
    }
  }
};

}

#endif
