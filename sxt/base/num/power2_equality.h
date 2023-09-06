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

#include "sxt/base/macro/cuda_callable.h"

namespace sxt::basn {
//--------------------------------------------------------------------------------------------------
// is_power2
//--------------------------------------------------------------------------------------------------
// returns 1 in case n is a power of 2. Returns 0 otherwise
CUDA_CALLABLE
inline bool is_power2(unsigned long long n) noexcept { return (n != 0) && ((n & (n - 1)) == 0); }
} // namespace sxt::basn
