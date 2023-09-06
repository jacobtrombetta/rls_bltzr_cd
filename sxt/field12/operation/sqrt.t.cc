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
#include "sxt/field12/operation/sqrt.h"

#include "sxt/base/test/unit_test.h"
#include "sxt/field12/operation/square.h"
#include "sxt/field12/type/element.h"

using namespace sxt;
using namespace sxt::f12o;

TEST_CASE("square root") {
  SECTION("returns a value that equals the original when squared") {
    // Random value between 1 and p_v generated using the SAGE library.
    constexpr f12t::element a{0x5e14fa3f799a1246, 0xd2684f55323a5290, 0x7f05158a2afce436,
                              0xe52da61b5953ed17, 0x8ed26f9683921f45, 0x03b2ad9ebab772aa};

    f12t::element ret_sqrt;
    auto result_is_correct = sqrt(ret_sqrt, a);
    REQUIRE(result_is_correct);

    f12t::element ret_square;
    square(ret_square, ret_sqrt);
    REQUIRE(ret_square == a);
  }
}
