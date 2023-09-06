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
/*
 * Adopted from zkcrypto/bls12_381
 *
 * Copyright (c) 2021
 * Sean Bowe <ewillbefull@gmail.com>
 * Jack Grigg <thestr4d@gmail.com>
 *
 * See third_party/license/zkcrypto.LICENSE
 */
#pragma once

#include <cstdint>

#include "sxt/base/macro/cuda_callable.h"

namespace sxt::f12b {
//--------------------------------------------------------------------------------------------------
// reduce
//--------------------------------------------------------------------------------------------------
/*
 The Montgomery reduction here is based on Algorithm 14.32 in
 Handbook of Applied Cryptography
 <http://cacr.uwaterloo.ca/hac/about/chap14.pdf>.
 */
CUDA_CALLABLE void reduce(uint64_t h[6], const uint64_t t[12]) noexcept;

//--------------------------------------------------------------------------------------------------
// is_below_modulus
//--------------------------------------------------------------------------------------------------
CUDA_CALLABLE bool is_below_modulus(const uint64_t h[6]) noexcept;
} // namespace sxt::f12b
