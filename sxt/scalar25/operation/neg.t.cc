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
#include "sxt/scalar25/operation/neg.h"

#include "sxt/base/test/unit_test.h"
#include "sxt/scalar25/type/element.h"
#include "sxt/scalar25/type/literal.h"

using namespace sxt::s25o;
using namespace sxt::s25t;

TEST_CASE("we check the zero value addition") {
  element s;
  neg(s, 0x0_s25);
  REQUIRE(s == 0x0_s25);
}

TEST_CASE("double negation have no effect") {
  element s;
  neg(s, 0x3_s25);

  // negating s again should give us the first value % L
  neg(s, s);
  REQUIRE(s == 0x3_s25);
}

TEST_CASE("there is only one negative inverse for each number") {
  element s;
  neg(s, 0x3_s25);
  REQUIRE(s == 0x1000000000000000000000000000000014def9dea2f79cd65812631a5cf5d3ea_s25);

  // negating s again should give us the first value % L
  neg(s, s);
  REQUIRE(s == 0x3_s25);
}

TEST_CASE("the L order has 0 as negative inverse") {
  element s;
  // 2^252 + 27742317777372353535851937790883648493
  neg(s, 0x1000000000000000000000000000000014def9dea2f79cd65812631a5cf5d3ed_s25);
  REQUIRE(s == 0x0_s25);
}

TEST_CASE("we correctly negate A when A is the biggest 256bits integer") {
  element s;

  neg(s, 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff_s25);
  REQUIRE(s == 0x14def9dea2f79cd65812631a5cf5d3ed1_s25);

  // negating s again should give us the first value % L
  neg(s, s);
  // 0xffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff_s25 % L
  REQUIRE(s == 0xffffffffffffffffffffffffffffffec6ef5bf4737dcf70d6ec31748d98951c_s25);
}
