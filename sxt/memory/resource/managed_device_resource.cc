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
#include "sxt/memory/resource/managed_device_resource.h"

#include <cuda_runtime.h>

#include <string>

#include "sxt/base/error/panic.h"

namespace sxt::memr {
//--------------------------------------------------------------------------------------------------
// do_allocate
//--------------------------------------------------------------------------------------------------
void* managed_device_resource::do_allocate(size_t bytes, size_t /*alignment*/) noexcept {
  void* res;
  auto rcode = cudaMallocManaged(&res, bytes);
  if (rcode != cudaSuccess) {
    baser::panic("cudaMallocManaged failed: " + std::string{cudaGetErrorString(rcode)});
  }
  return res;
}

//--------------------------------------------------------------------------------------------------
// do_deallocate
//--------------------------------------------------------------------------------------------------
void managed_device_resource::do_deallocate(void* ptr, size_t /*bytes*/,
                                            size_t /*alignment*/) noexcept {
  auto rcode = cudaFree(ptr);
  if (rcode != cudaSuccess) {
    baser::panic("cudaFree failed: " + std::string{cudaGetErrorString(rcode)});
  }
}

//--------------------------------------------------------------------------------------------------
// do_is_equal
//--------------------------------------------------------------------------------------------------
bool managed_device_resource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
  return this == &other;
}

//--------------------------------------------------------------------------------------------------
// get_managed_device_resource
//--------------------------------------------------------------------------------------------------
managed_device_resource* get_managed_device_resource() noexcept {
  // Use a heap allocated object that never gets deleted since we want this
  // to be available for the program duration.
  //
  // See https://google.github.io/styleguide/cppguide.html#Static_and_Global_Variables for
  // details on this use case.
  static managed_device_resource* resource = new managed_device_resource{};

  return resource;
}
} // namespace sxt::memr
