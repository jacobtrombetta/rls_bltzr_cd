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
#include "sxt/multiexp/index/index_table_utility.h"

#include "sxt/base/error/assert.h"
#include "sxt/multiexp/index/index_table.h"

namespace sxt::mtxi {
//--------------------------------------------------------------------------------------------------
// init_rows
//--------------------------------------------------------------------------------------------------
void init_rows(index_table& table, basct::cspan<size_t> sizes) noexcept {
  SXT_DEBUG_ASSERT(table.num_rows() == sizes.size());
  auto entry_data = table.entry_data();
  auto rows = table.header();
  for (size_t row_index = 0; row_index < sizes.size(); ++row_index) {
    rows[row_index] = {entry_data, 0};
    entry_data += sizes[row_index];
  }
}
} // namespace sxt::mtxi
