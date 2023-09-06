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

namespace sxt::algb {
//--------------------------------------------------------------------------------------------------
// reducer
//--------------------------------------------------------------------------------------------------
/**
 * Describe a generic reduction function that can be used in CUDA kernels.
 * See https://developer.download.nvidia.com/assets/cuda/files/reduction.pdf
 */
template <class R>
concept reducer = requires(typename R::value_type& x, typename R::value_type& xv,
                           typename R::value_type& yv, typename R::value_type& z) {
  { R::accumulate_inplace(x, z) } noexcept;
  { R::accumulate_inplace(xv, yv) } noexcept;
};
} // namespace sxt::algb
