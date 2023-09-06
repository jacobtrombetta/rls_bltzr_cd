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

#include <memory>

namespace sxt::xens {
//--------------------------------------------------------------------------------------------------
// pending_event
//--------------------------------------------------------------------------------------------------
class pending_event {
public:
  virtual ~pending_event() noexcept = default;

  void set_next(std::unique_ptr<pending_event>&& next) noexcept;

  std::unique_ptr<pending_event> release_next() noexcept { return {std::move(next_)}; }

  pending_event* next() noexcept { return next_.get(); }

  virtual void invoke(int device) noexcept = 0;

private:
  std::unique_ptr<pending_event> next_;
};
} // namespace sxt::xens
