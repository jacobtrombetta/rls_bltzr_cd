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
/**
 * Adopted from libsodium
 *
 * Copyright (c) 2013-2023
 * Frank Denis <j at pureftpd dot org>
 *
 * See third_party/license/libsodium.LICENSE
 */
#pragma once

#include "sxt/base/macro/cuda_callable.h"

namespace sxt::c21t {
struct element_cached;
}

namespace sxt::c21o {
//--------------------------------------------------------------------------------------------------
// cmov
//--------------------------------------------------------------------------------------------------
CUDA_CALLABLE
void cmov(c21t::element_cached& t, const c21t::element_cached& u, unsigned char b) noexcept;

//--------------------------------------------------------------------------------------------------
// cmov8
//--------------------------------------------------------------------------------------------------
CUDA_CALLABLE void cmov8(c21t::element_cached& t, const c21t::element_cached cached[8],
                         const signed char b) noexcept;
} // namespace sxt::c21o
