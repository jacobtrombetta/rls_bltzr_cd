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
#include "sxt/execution/schedule/scheduler.h"

#include <iostream>
#include <tuple>
#include <vector>

#include "sxt/base/test/unit_test.h"
#include "sxt/execution/schedule/test_pending_event.h"
#include "sxt/execution/schedule/test_pollable_event.h"

using namespace sxt;
using namespace sxt::xens;

TEST_CASE("we can schedule pollable events to run") {
  scheduler sched{3, 2};

  std::vector<int> ids;
  auto f = [&](int id) noexcept { ids.push_back(id); };

  std::vector<std::tuple<int, int>> pending_ids;
  auto pending_f = [&](int id, int device) noexcept { pending_ids.emplace_back(id, device); };

  SECTION("we can run with no events") { sched.run(); }

  SECTION("we can schedule a single event") {
    sched.schedule(std::make_unique<test_pollable_event>(0, 1, f));
    sched.run();
    std::vector<int> expected = {0};
    REQUIRE(ids == expected);
  }

  SECTION("we can schedule multiple events") {
    sched.schedule(std::make_unique<test_pollable_event>(0, 10, f));
    sched.schedule(std::make_unique<test_pollable_event>(1, 5, f));
    sched.run();
    std::vector<int> expected = {1, 0};
    REQUIRE(ids == expected);
  }

  SECTION("we can schedule pending events") {
    for (int i = 0; i < 2; ++i) {
      sched.schedule(std::make_unique<test_pollable_event>(0, 1, f));
      sched.schedule(std::make_unique<test_pollable_event>(1, 1, f));
      sched.schedule(std::make_unique<test_pollable_event>(2, 1, f));
    }
    sched.schedule(std::make_unique<test_pending_event>(3, pending_f));
    sched.run();
    std::vector<int> expected = {2, 1, 0, 2, 1, 0};
    REQUIRE(ids == expected);
    std::vector<std::tuple<int, int>> expected_pending_ids = {{3, 2}};
    REQUIRE(pending_ids == expected_pending_ids);
  }
}
