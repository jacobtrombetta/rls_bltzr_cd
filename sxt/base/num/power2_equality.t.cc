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
#include "sxt/base/num/power2_equality.h"

#include "sxt/base/test/unit_test.h"

using namespace sxt::basn;

TEST_CASE("we check if a number is a power of 2") {
  REQUIRE(!is_power2(0));
  REQUIRE(is_power2(1));
  REQUIRE(is_power2(2));
  REQUIRE(!is_power2(3));
  REQUIRE(is_power2(4));
  REQUIRE(!is_power2(5));
  REQUIRE(!is_power2(6));
  REQUIRE(!is_power2(7));
  REQUIRE(is_power2(8));
  REQUIRE(is_power2(1ULL << 63));
  REQUIRE(!is_power2((1ULL << 63) - 1));
  REQUIRE(!is_power2((1ULL << 63) + 1));
  REQUIRE(!is_power2(0xffffffffffffffff));
  REQUIRE(!is_power2(0xffffffffffffffff - 1));
}
