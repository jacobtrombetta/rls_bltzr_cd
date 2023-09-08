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

#include <cassert>
#include <concepts>

#include "sxt/algorithm/base/mapper.h"
#include "sxt/algorithm/base/reducer.h"
#include "sxt/algorithm/reduction/thread_reduction.h"
#include "sxt/execution/kernel/launch.h"
#include "sxt/multiexp/multiproduct_gpu/block_computation_descriptor.h"

namespace sxt::mtxmpg {
//--------------------------------------------------------------------------------------------------
// multiproduct_kernel
//--------------------------------------------------------------------------------------------------
template <algb::reducer Reducer, algb::mapper Mapper>
  requires std::same_as<typename Reducer::value_type, typename Mapper::value_type> &&
           std::constructible_from<Mapper, const typename Reducer::value_type*, const unsigned*>
__global__ void multiproduct_kernel(typename Reducer::value_type* out,
                                    const typename Reducer::value_type* generators,
                                    const unsigned* indexes,
                                    const block_computation_descriptor* block_descriptors) {
  using T = typename Reducer::value_type;
  extern __shared__ T shared_data_p[];
  T* shared_data = shared_data_p;
  auto thread_index = threadIdx.x;
  auto block_index = blockIdx.x;
  auto descriptor = block_descriptors[block_index];
  Mapper mapper{generators, indexes + descriptor.index_first};
  // Note: It's expected that most products will be of similar length and
  // hence share a common block size, but we allow for the same kernel to
  // compute product reductions with varying block sizes.
  xenk::launch_kernel(
      descriptor.block_size,
      [=]<unsigned BlockSize>(std::integral_constant<unsigned, BlockSize>) noexcept {
        assert(block_index >= descriptor.block_offset);
        auto index = (block_index - descriptor.block_offset) * (BlockSize * 2) + thread_index;
        auto step = BlockSize * 2 * descriptor.reduction_num_blocks;
        // If BlockSize is less than the maximum block size (the size the kernel was launched with),
        // then treat the some of the threads as inactive.
        if (thread_index < BlockSize) {
          algr::thread_reduce<Reducer, BlockSize>(out + block_index, shared_data, mapper,
                                                  descriptor.n, step, thread_index, index);
        }
      });
}
} // namespace sxt::mtxmpg
