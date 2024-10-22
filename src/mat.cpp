#include "mat.h"

#include <catch2/catch_test_macros.hpp>

namespace marlon {
namespace math {
static_assert(sizeof(Mat2x2i) == 16);
static_assert(sizeof(Mat2x2f) == 16);
static_assert(sizeof(Mat2x2d) == 32);
static_assert(sizeof(Mat2x3i) == 24);
static_assert(sizeof(Mat2x3f) == 24);
static_assert(sizeof(Mat2x3d) == 48);
static_assert(sizeof(Mat2x4i) == 32);
static_assert(sizeof(Mat2x4f) == 32);
static_assert(sizeof(Mat2x4d) == 64);
static_assert(sizeof(Mat3x2i) == 24);
static_assert(sizeof(Mat3x2f) == 24);
static_assert(sizeof(Mat3x2d) == 48);
static_assert(sizeof(Mat3x3i) == 36);
static_assert(sizeof(Mat3x3f) == 36);
static_assert(sizeof(Mat3x3d) == 72);
static_assert(sizeof(Mat3x4i) == 48);
static_assert(sizeof(Mat3x4f) == 48);
static_assert(sizeof(Mat3x4d) == 96);
static_assert(sizeof(Mat4x2i) == 32);
static_assert(sizeof(Mat4x2f) == 32);
static_assert(sizeof(Mat4x2d) == 64);
static_assert(sizeof(Mat4x3i) == 48);
static_assert(sizeof(Mat4x3f) == 48);
static_assert(sizeof(Mat4x3d) == 96);
static_assert(sizeof(Mat4x4i) == 64);
static_assert(sizeof(Mat4x4f) == 64);
static_assert(sizeof(Mat4x4d) == 128);

TEST_CASE("Matrices can be multiplied") {
  Mat2x2i const a{{1, 2}, {3, 4}};
  Mat2x2i const b{{5, 6}, {7, 8}};
  Mat2x2i const ab{{1 * 5 + 2 * 7, 1 * 6 + 2 * 8},
                   {3 * 5 + 4 * 7, 3 * 6 + 4 * 8}};
  REQUIRE(a * b == ab);
}
} // namespace math
} // namespace marlon