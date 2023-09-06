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
#include "sxt/memory/management/managed_array.h"

#include <cstring>

namespace sxt::memmg {
//--------------------------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------------------------
managed_array<void>::managed_array(void* data, size_t size, size_t num_bytes,
                                   allocator_type alloc) noexcept
    : alloc_{alloc}, data_{data}, size_{size}, num_bytes_{num_bytes} {}

managed_array<void>::managed_array(const managed_array& other) noexcept
    : managed_array{other, other.get_allocator()} {}

managed_array<void>::managed_array(const managed_array& other, allocator_type alloc) noexcept
    : alloc_{alloc} {
  this->operator=(other);
}

managed_array<void>::managed_array(managed_array&& other) noexcept
    : managed_array{std::move(other), other.get_allocator()} {}

managed_array<void>::managed_array(managed_array&& other, allocator_type alloc) noexcept
    : alloc_{alloc} {
  this->operator=(std::move(other));
}

//--------------------------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------------------------
managed_array<void>::~managed_array() noexcept { this->reset(); }

//--------------------------------------------------------------------------------------------------
// assignment
//--------------------------------------------------------------------------------------------------
managed_array<void>& managed_array<void>::operator=(const managed_array& other) noexcept {
  if (this == &other) {
    return *this;
  }
  this->reset();
  num_bytes_ = other.num_bytes_;
  size_ = other.size_;
  data_ = static_cast<void*>(alloc_.allocate(num_bytes_));
  std::memcpy(data_, other.data_, num_bytes_);
  return *this;
}

managed_array<void>& managed_array<void>::operator=(managed_array&& other) noexcept {
  if (this->get_allocator() != other.get_allocator()) {
    return this->operator=(other);
  }
  this->reset();

  num_bytes_ = other.num_bytes_;
  size_ = other.size_;
  data_ = other.data_;

  other.num_bytes_ = 0;
  other.size_ = 0;
  other.data_ = nullptr;

  return *this;
}

//--------------------------------------------------------------------------------------------------
// shrink
//--------------------------------------------------------------------------------------------------
void managed_array<void>::shrink(size_t size) noexcept {
  SXT_DEBUG_ASSERT(size <= size_);
  size_ = size;
}

//--------------------------------------------------------------------------------------------------
// reset
//--------------------------------------------------------------------------------------------------
void managed_array<void>::reset() noexcept {
  if (data_ == nullptr) {
    return;
  }
  alloc_.deallocate(reinterpret_cast<std::byte*>(data_), num_bytes_);
  data_ = nullptr;
  num_bytes_ = 0;
  size_ = 0;
}
} // namespace sxt::memmg
