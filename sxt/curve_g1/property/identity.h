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
#include "sxt/curve_g1/type/element_affine.h"
#include "sxt/curve_g1/type/element_p2.h"
#include "sxt/field12/property/zero.h"

namespace sxt::cg1p {
//--------------------------------------------------------------------------------------------------
// is_identity
//--------------------------------------------------------------------------------------------------
CUDA_CALLABLE
inline bool is_identity(const cg1t::element_affine& p) noexcept { return p.infinity; }

//--------------------------------------------------------------------------------------------------
// is_identity
//--------------------------------------------------------------------------------------------------
CUDA_CALLABLE
inline bool is_identity(const cg1t::element_p2& p) noexcept { return f12p::is_zero(p.Z); }
} // namespace sxt::cg1p
