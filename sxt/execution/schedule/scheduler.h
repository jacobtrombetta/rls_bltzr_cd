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

#include "sxt/execution/schedule/active_scheduler.h"
#include "sxt/execution/schedule/pending_scheduler.h"

namespace sxt::xens {
class pollable_event;
class pending_event;

//--------------------------------------------------------------------------------------------------
// scheduler
//--------------------------------------------------------------------------------------------------
class scheduler {
public:
  scheduler(size_t num_devices, size_t target_max_active) noexcept;

  void run() noexcept;

  void schedule(std::unique_ptr<pollable_event>&& event) noexcept;

  void schedule(std::unique_ptr<pending_event>&& event) noexcept;

  int get_available_device() const noexcept;

private:
  active_scheduler active_scheduler_;
  pending_scheduler pending_scheduler_;
};

//--------------------------------------------------------------------------------------------------
// get_scheduler
//--------------------------------------------------------------------------------------------------
scheduler& get_scheduler() noexcept;
} // namespace sxt::xens
