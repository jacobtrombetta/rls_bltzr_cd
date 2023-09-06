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

#include <cstddef>
#include <memory_resource>
#include <random>

#include "sxt/base/container/span.h"
#include "sxt/base/memory/alloc.h"

namespace sxt::mtxb {
struct exponent_sequence;
}
namespace sxt::c21t {
struct element_p3;
}

namespace sxt::mtxrn {
struct random_multiexponentiation_descriptor;

//--------------------------------------------------------------------------------------------------
// generate_random_multiexponentiation
//--------------------------------------------------------------------------------------------------
void generate_random_multiexponentiation(
    uint64_t& num_inputs, basct::span<mtxb::exponent_sequence>& exponents, basm::alloc_t alloc,
    std::mt19937& rng, const random_multiexponentiation_descriptor& descriptor) noexcept;

void generate_random_multiexponentiation(
    basct::span<uint64_t>& inputs, basct::span<mtxb::exponent_sequence>& exponents,
    basm::alloc_t alloc, std::mt19937& rng,
    const random_multiexponentiation_descriptor& descriptor) noexcept;

void generate_random_multiexponentiation(
    basct::span<c21t::element_p3>& inputs, basct::span<mtxb::exponent_sequence>& exponents,
    basm::alloc_t alloc, std::mt19937& rng,
    const random_multiexponentiation_descriptor& descriptor) noexcept;
} // namespace sxt::mtxrn
