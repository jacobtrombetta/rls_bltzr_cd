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

#include "sxt/base/container/span.h"

namespace sxt::c21t {
struct element_p3;
}
namespace sxt::mtxb {
struct exponent_sequence;
}

namespace sxt::mtxtst {
//--------------------------------------------------------------------------------------------------
// sum_curve21_elements
//--------------------------------------------------------------------------------------------------
void sum_curve21_elements(basct::span<c21t::element_p3> result,
                          basct::cspan<basct::cspan<uint64_t>> terms,
                          basct::cspan<c21t::element_p3> inputs) noexcept;

//--------------------------------------------------------------------------------------------------
// mul_sum_curve21_elements
//--------------------------------------------------------------------------------------------------
void mul_sum_curve21_elements(basct::span<c21t::element_p3> result,
                              basct::cspan<c21t::element_p3> generators,
                              basct::cspan<mtxb::exponent_sequence> sequences) noexcept;
} // namespace sxt::mtxtst
