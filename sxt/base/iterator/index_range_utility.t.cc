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
#include "sxt/base/iterator/index_range_utility.h"

#include <iterator>

#include "sxt/base/iterator/index_range.h"
#include "sxt/base/iterator/index_range_iterator.h"
#include "sxt/base/test/unit_test.h"

using namespace sxt;
using namespace sxt::basit;

TEST_CASE("we can split an index_range") {
  SECTION("we handle the n=1 case") {
    auto [first, last] = split(index_range{1, 9}, 1);
    REQUIRE(std::distance(first, last) == 1);
    REQUIRE(*first == index_range{1, 9});
  }

  SECTION("we can split an empty range") {
    auto [first, last] = split(index_range{3, 3}, 1);
    REQUIRE(std::distance(first, last) == 0);
  }

  SECTION("we handle the case when n is greater than 1") {
    auto [iter, last] = split(index_range{1, 5}, 2);
    REQUIRE(std::distance(iter, last) == 2);
    REQUIRE(*iter++ == index_range{1, 3});
    REQUIRE(*iter++ == index_range{3, 5});
    REQUIRE(iter == last);
  }

  SECTION("we handle the case when n doesn't divide the range size") {
    auto [iter, last] = split(index_range{1, 5}, 3);
    REQUIRE(std::distance(iter, last) == 2);
    REQUIRE(*iter++ == index_range{1, 3});
    REQUIRE(*iter++ == index_range{3, 5});
    REQUIRE(iter == last);
  }

  SECTION("we handle the case when n is greater than the range") {
    auto [iter, last] = split(index_range{1, 3}, 10);
    REQUIRE(std::distance(iter, last) == 2);
    REQUIRE(*iter++ == index_range{1, 2});
    REQUIRE(*iter++ == index_range{2, 3});
    REQUIRE(iter == last);
  }
}
