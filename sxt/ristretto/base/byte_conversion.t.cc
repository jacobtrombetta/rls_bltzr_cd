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
#include "sxt/ristretto/base/byte_conversion.h"

#include <array>

#include "sxt/base/test/unit_test.h"
#include "sxt/curve21/type/element_p3.h"

using namespace sxt;
using namespace sxt::rstb;

TEST_CASE("Testing 1 - point conversion from curve255 to ristretto") {
  c21t::element_p3 p = {
      {1289220534039435, 2189782176109648, 71385226900448, 1597582282759429, 1149951793871729},
      {1101169981211898, 1452568463355513, 809819081938490, 965950159365841, 527316475871724},
      {1373551439462324, 257663321601115, 2062204210432847, 1931252135961392, 376387980511738},
      {1064943153583052, 547602618132901, 1233678055816325, 755391245238190, 611164212907866}};

  SECTION("verify against values from libsodium") {
    std::array<uint8_t, 32> s;

    to_bytes(s.data(), p);

    std::array<uint8_t, 32> expected_s = {48,  102, 248, 42,  26,  116, 125, 69, 18,  13,  23,
                                          64,  241, 67,  88,  83,  26,  143, 4,  187, 255, 230,
                                          168, 25,  248, 109, 254, 80,  244, 74, 10,  70};

    REQUIRE(s == expected_s);
  }
}

TEST_CASE("Testing 2 - point conversion from curve255 to ristretto") {
  c21t::element_p3 p = {
      {940982861241073, 941784475676028, 1130550519223950, 1055054750816951, 1217994276021278},
      {1468150475035081, 1679865258693596, 1553095549552768, 1492975360999298, 92415319781264},
      {322327336398557, 2095768576231787, 655955884584774, 1649222581624072, 857401572457097},
      {1409721664202831, 312686946680975, 697482901591576, 1069363237063803, 997986709184113},
  };

  SECTION("verify against values from libsodium") {
    std::array<uint8_t, 32> s;

    to_bytes(s.data(), p);

    std::array<uint8_t, 32> expected_s = {174, 129, 231, 222, 223, 32,  164, 151, 225, 12, 48,
                                          74,  118, 92,  23,  103, 164, 45,  110, 6,   2,  151,
                                          88,  210, 215, 232, 239, 124, 196, 196, 17,  121};

    REQUIRE(s == expected_s);
  }
}

TEST_CASE("Testing 3 - point conversion from ristretto to curve255") {
  c21t::element_p3 p;
  std::array<uint8_t, 32> s;

  std::array<uint8_t, 32> expected_s = {174, 129, 231, 222, 223, 32,  164, 151, 225, 12, 48,
                                        74,  118, 92,  23,  103, 164, 45,  110, 6,   2,  151,
                                        88,  210, 215, 232, 239, 124, 196, 196, 17,  121};

  SECTION("verify against values from libsodium") {
    from_bytes(p, expected_s.data());

    to_bytes(s.data(), p);

    REQUIRE(s == expected_s);
  }
}

TEST_CASE("Testing 4 - point conversion from ristretto to curve255") {
  std::array<uint8_t, 32> s = {174, 129, 231, 222, 223, 32,  164, 151, 225, 12, 48,
                               74,  118, 92,  23,  103, 164, 45,  110, 6,   2,  151,
                               88,  210, 215, 232, 239, 124, 196, 196, 17,  121};

  SECTION("verify against values from libsodium") {
    c21t::element_p3 p;
    c21t::element_p3 expected_p = {
        {940982861241073, 941784475676028, 1130550519223950, 1055054750816951, 1217994276021278},
        {1468150475035081, 1679865258693596, 1553095549552768, 1492975360999298, 92415319781264},
        {322327336398557, 2095768576231787, 655955884584774, 1649222581624072, 857401572457097},
        {1409721664202831, 312686946680975, 697482901591576, 1069363237063803, 997986709184113},
    };

    from_bytes(p, s.data());

    REQUIRE(p == expected_p);
  }
}
