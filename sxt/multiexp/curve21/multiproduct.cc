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
#include "sxt/multiexp/curve21/multiproduct.h"

#include "sxt/algorithm/base/gather_mapper.h"
#include "sxt/base/macro/cuda_callable.h"
#include "sxt/curve21/operation/accumulator.h"
#include "sxt/curve21/operation/neg.h"
#include "sxt/execution/async/future.h"
#include "sxt/multiexp/multiproduct_gpu/multiproduct.h"

namespace sxt::mtxc21 {
//--------------------------------------------------------------------------------------------------
// signed_mapper
//--------------------------------------------------------------------------------------------------
namespace {
class signed_mapper {
public:
  using value_type = c21t::element_p3;

  CUDA_CALLABLE signed_mapper(const c21t::element_p3* generators, const unsigned* indexes) noexcept
      : generators_{generators}, indexes_{indexes} {}

  CUDA_CALLABLE void map_index(c21t::element_p3& val, unsigned int index) const noexcept {
    constexpr auto sign_bit = 1u << 31;
    auto i = indexes_[index];
    auto is_neg = static_cast<unsigned>((i & sign_bit) != 0);
    i = i & ~sign_bit;
    val = generators_[i];
    c21o::cneg(val, is_neg);
  }

  CUDA_CALLABLE c21t::element_p3 map_index(unsigned int index) const noexcept {
    c21t::element_p3 res;
    this->map_index(res, index);
    return res;
  }

private:
  const c21t::element_p3* generators_;
  const unsigned* indexes_;
};
} // namespace

//--------------------------------------------------------------------------------------------------
// async_compute_multiproduct
//--------------------------------------------------------------------------------------------------
xena::future<> async_compute_multiproduct(basct::span<c21t::element_p3> products,
                                          const basdv::stream& stream,
                                          basct::cspan<c21t::element_p3> generators,
                                          basct::cspan<unsigned> indexes,
                                          basct::cspan<unsigned> product_sizes,
                                          bool is_signed) noexcept {
  if (!is_signed) {
    using Mapper = algb::gather_mapper<c21t::element_p3>;
    return mtxmpg::compute_multiproduct<c21o::accumulator, Mapper>(products, stream, generators,
                                                                   indexes, product_sizes);
  }
  return mtxmpg::compute_multiproduct<c21o::accumulator, signed_mapper>(
      products, stream, generators, indexes, product_sizes);
}
} // namespace sxt::mtxc21
