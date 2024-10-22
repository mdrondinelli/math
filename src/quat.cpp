#ifndef CATCH_CONFIG_DISABLE

#include "quat.h"

#include <catch2/catch_test_macros.hpp>

namespace marlon {
namespace math {
TEST_CASE("Quaternions can be constructed.") {
  const Quatf p{4.0f, {1.0f, 2.0f, 3.0f}};
  REQUIRE(p.w == 4.0f);
  REQUIRE(p.v == Vec3f{1.0f, 2.0f, 3.0f});
  const auto q = Quatf::identity();
  REQUIRE(q.w == 1.0f);
  REQUIRE(q.v == Vec3f::zero());
}

TEST_CASE("Quaternions can be compared.") {
  const Quatf p{1.0f, {1.0f, 0.0f, 0.0f}};
  const Quatf q{1.0f, {0.0f, 0.0f, 0.0f}};
  REQUIRE(p == p);
  REQUIRE(p != q);
}

TEST_CASE("Quaternions can be negated.") {
  const Quatf q{1.0f, {2.0f, 3.0f, 4.0f}};
  const Quatf minus_q{-1.0f, {-2.0f, -3.0f, -4.0f}};
  REQUIRE(-q == minus_q);
}

TEST_CASE("Quaternions can be multiplied by scalars.") {
  const auto q = Quatf::identity();
  const auto s = 2.0f;
  const auto product = Quatf{2.0f, {0.0f, 0.0f, 0.0f}};
  REQUIRE(s * q == product);
  REQUIRE(q * s == product);
}

TEST_CASE("Quaternions can be multiplied by quaternions.") {
  const auto p = Quatf::identity();
  const auto q = Quatf::identity();
  REQUIRE(p * q == Quatf::identity());
}

TEST_CASE("Quaternions can be divided by scalars.") {
  const auto q = Quatf::identity();
  const auto s = 2.0f;
  const auto quotient = Quatf{0.5f, {0.0f, 0.0f, 0.0f}};
  REQUIRE(q / s == quotient);
}

TEST_CASE("Quaternions can be added to quaternions.") {
  const auto q = Quatf::identity();
  const auto p = Quatf::identity();
  const auto sum = Quatf{2.0f, {0.0f, 0.0f, 0.0f}};
  REQUIRE(p + q == sum);
}

TEST_CASE("Quaternions can be subtracted from quaternions.") {
  const auto p = Quatf::identity();
  const auto q = Quatf::identity();
  const auto difference = Quatf{0.0f, {0.0f, 0.0f, 0.0f}};
  REQUIRE(p - q == difference);
}

TEST_CASE("Quaternions can have their length taken.") {
  auto const q = Quatf::identity();
  REQUIRE(length_squared(q) == 1.0f);
  REQUIRE(length(q) == 1.0f);
}

TEST_CASE("Quaternions can be normalized.") {
  auto const p = Quatf{4.0f, {0.0f, 0.0f, 0.0f}};
  auto const q = normalize(p);
  REQUIRE(q == Quatf::identity());
}
} // namespace math
} // namespace marlon

#endif