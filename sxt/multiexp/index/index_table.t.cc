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
#include "sxt/multiexp/index/index_table.h"

#include <sstream>

#include "sxt/base/test/allocator_aware.h"
#include "sxt/base/test/unit_test.h"

using namespace sxt;
using namespace sxt::mtxi;

TEST_CASE("index_table manages a table of 64-bit index values") {
  SECTION("we can construct a table from an initializer list") {
    index_table tbl{{1, 2}, {3, 4, 5}};
    auto hdr = tbl.header();

    REQUIRE(hdr.size() == 2);

    REQUIRE(hdr[0].size() == 2);
    REQUIRE(hdr[0][0] == 1);
    REQUIRE(hdr[0][1] == 2);

    REQUIRE(hdr[1].size() == 3);
    REQUIRE(hdr[1][0] == 3);
    REQUIRE(hdr[1][1] == 4);
    REQUIRE(hdr[1][2] == 5);
  }

  SECTION("we can compare index tables") {
    index_table tbl1{{1}, {7, 9, 13}, {5, 2}};
    index_table tbl2{{1}, {7, 9, 13}, {5, 11}};
    index_table tbl3;
    REQUIRE(tbl1 == tbl1);
    REQUIRE(tbl1 != tbl2);
    REQUIRE(tbl1 != tbl3);
  }

  SECTION("we can print a table") {
    index_table tbl{};
    std::ostringstream oss;

    oss << tbl;
    REQUIRE(oss.str() == "{}");
    oss.clear();

    oss = std::ostringstream{};
    tbl = {{1}, {2, 3}};
    oss << tbl;
    REQUIRE(oss.str() == "{{1},{2,3}}");
    oss.clear();
  }

  SECTION("verify allocator-aware operations") {
    index_table tbl{{1}, {2, 3}, {4}};
    bastst::exercise_allocator_aware_operations(tbl);
  }
}
