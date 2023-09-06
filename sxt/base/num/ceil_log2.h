/** Proofs GPU - Space and Time's cryptographic proof algorithms on the CPU and GPU.
 *
 * Copyright 2023-present Space and Time Labs, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include <cstdint>

#include "sxt/base/bit/count.h"
#include "sxt/base/error/assert.h"
#include "sxt/base/num/power2_equality.h"

namespace sxt::basn {
//--------------------------------------------------------------------------------------------------
// ceil_log2
//--------------------------------------------------------------------------------------------------
// returns ceil(log2(n)).
//
// assert in case n is zero
inline int ceil_log2(uint64_t n) noexcept {
  SXT_DEBUG_ASSERT(n != 0);

  if (is_power2(n)) {
    return basbt::count_trailing_zeros(n);
  }

  return 64 - basbt::count_leading_zeros(n);
}
} // namespace sxt::basn
