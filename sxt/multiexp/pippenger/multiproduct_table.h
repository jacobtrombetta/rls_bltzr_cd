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

#include <array>
#include <cstdint>

#include "sxt/base/container/span.h"

namespace sxt::basct {
class blob_array;
}
namespace sxt::mtxb {
class exponent_sequence;
} // namespace sxt::mtxb
namespace sxt::mtxi {
class index_table;
}

namespace sxt::mtxpi {
//--------------------------------------------------------------------------------------------------
// make_digit_index_array
//--------------------------------------------------------------------------------------------------
size_t make_digit_index_array(basct::span<size_t> array, size_t first,
                              basct::cspan<uint8_t> or_all) noexcept;

//--------------------------------------------------------------------------------------------------
// make_multiproduct_table
//--------------------------------------------------------------------------------------------------
size_t make_multiproduct_table(mtxi::index_table& table,
                               basct::cspan<mtxb::exponent_sequence> exponents, size_t max_entries,
                               const basct::blob_array& term_or_all,
                               const basct::blob_array& output_digit_or_all,
                               size_t radix_log2) noexcept;
} // namespace sxt::mtxpi
