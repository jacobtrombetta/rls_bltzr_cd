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
/**
 * Adopted from libsodium
 *
 * Copyright (c) 2013-2023
 * Frank Denis <j at pureftpd dot org>
 *
 * See third_party/license/libsodium.LICENSE
 */

#include "sxt/curve21/type/double_impl.h"

#include "sxt/curve21/type/element_p1p1.h"
#include "sxt/curve21/type/element_p2.h"
#include "sxt/field51/operation/add.h"
#include "sxt/field51/operation/sq.h"
#include "sxt/field51/operation/sub.h"
#include "sxt/field51/type/element.h"

namespace sxt::c21t {
//--------------------------------------------------------------------------------------------------
// double_element_impl
//--------------------------------------------------------------------------------------------------
/*
 r = 2 * p
*/
CUDA_CALLABLE
void double_element_impl(c21t::element_p1p1& r, const c21t::element_p2& p) noexcept {
  f51t::element t0;

  f51o::sq(r.X, p.X);
  f51o::sq(r.Z, p.Y);
  f51o::sq2(r.T, p.Z);
  f51o::add(r.Y, p.X, p.Y);
  f51o::sq(t0, r.Y);
  f51o::add(r.Y, r.Z, r.X);
  f51o::sub(r.Z, r.Z, r.X);
  f51o::sub(r.X, t0, r.Y);
  f51o::sub(r.T, r.T, r.Z);
}
} // namespace sxt::c21t
