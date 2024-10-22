#include "vec.h"

#include <catch2/catch_test_macros.hpp>

namespace marlon {
namespace math {
static_assert(sizeof(Vec2i) == 8);
static_assert(sizeof(Vec2f) == 8);
static_assert(sizeof(Vec2d) == 16);
static_assert(sizeof(Vec3i) == 12);
static_assert(sizeof(Vec3f) == 12);
static_assert(sizeof(Vec3d) == 24);
static_assert(sizeof(Vec4i) == 16);
static_assert(sizeof(Vec4f) == 16);
static_assert(sizeof(Vec4d) == 32);

TEST_CASE("Vectors can be constructed.") {
  const Vec2i i{1, 0};
  REQUIRE(i.x == 1);
  REQUIRE(i.y == 0);
  const Vec2f u = static_cast<Vec2f>(i);
  REQUIRE(u.x == 1.0f);
  REQUIRE(u.y == 0.0f);
}

TEST_CASE("Vectors can be compared.") {
  const Vec2i u{1, 0};
  const Vec2i v{0, 1};
  const Vec2i i{1, 0};
  REQUIRE(u != v);
  REQUIRE(u == i);
}

TEST_CASE("Vectors can be negated.") {
  const Vec2i v{1, 2};
  const Vec2i minus_v{-1, -2};
  REQUIRE(+v == v);
  REQUIRE(-v == minus_v);
}

TEST_CASE("Vectors can be added.") {
  const Vec2i u{1, 3};
  const Vec2i v{2, 4};
  const Vec2i u_plus_v{3, 7};
  REQUIRE(u + v == u_plus_v);
  auto w = u;
  w += v;
  REQUIRE(w == u_plus_v);
}

TEST_CASE("Vectors can be subracted.") {
  const Vec2i u{1, 3};
  const Vec2i v{2, 4};
  const Vec2i u_minus_v{-1, -1};
  REQUIRE(u - v == u_minus_v);
  auto w = u;
  w -= v;
  REQUIRE(w == u_minus_v);
}

TEST_CASE("Vectors can be multiplied with scalars.") {
  const Vec2i u{1, 3};
  const int s{3};
  const Vec2i u_times_s{3, 9};
  REQUIRE(s * u == u_times_s);
  auto v = u;
  v *= s;
  REQUIRE(v == u_times_s);
}

TEST_CASE("Vectors can be divided by scalars.") {
  const Vec2i u{1, 3};
  const int s{3};
  const Vec2i u_over_s{0, 1};
  REQUIRE(u / s == u_over_s);
  auto v = u;
  v /= s;
  REQUIRE(v == u_over_s);
}

TEST_CASE("The length of a vector can be taken") {
  const Vec2i u{3, 4};
  REQUIRE(length(u) == 5);
}
} // namespace math
} // namespace marlon