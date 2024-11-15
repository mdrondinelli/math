#ifndef MARLON_MATH_VEC_H
#define MARLON_MATH_VEC_H

#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>

#include <type_traits>
#include <utility>

#include "scalar.h"

namespace marlon {
static_assert(sizeof(float) == 4);
static_assert(sizeof(double) == 8);

template <typename T, int N> struct Vec;

template <typename T> struct Vec<T, 2> {
  T x;
  T y;

  static constexpr auto zero() noexcept {
    return Vec<T, 2>{T(0), T(0)};
  }

  static constexpr auto all(T s) noexcept {
    return Vec<T, 2>{s, s};
  }

  static constexpr auto x_axis() noexcept {
    return Vec<T, 2>{T(1), T(0)};
  }

  static constexpr auto y_axis() noexcept {
    return Vec<T, 2>{T(0), T(1)};
  }

  Vec() = default;

  constexpr Vec(T x, T y)
      : x{x}, y{y} {}

  template <typename F>
  constexpr explicit Vec(F &&f) noexcept(noexcept(f(0)))
      : x{f(0)}, y{f(1)} {}

  template <typename U>
  constexpr explicit Vec(Vec<U, 2> const &v) noexcept
      : x{static_cast<T>(v.x)}, y{static_cast<T>(v.y)} {}

  constexpr T const &operator[](int n) const noexcept {
    assert(n >= 0 && n < 2);
    switch (n) {
    case 0:
      return x;
    case 1:
      return y;
    default:
      std::unreachable();
    }
  }

  constexpr T &operator[](int n) noexcept {
    assert(n >= 0 && n < 2);
    switch (n) {
    case 0:
      return x;
    case 1:
      return y;
    default:
      std::unreachable();
    }
  }
};

template <typename T> struct Vec<T, 3> {
  T x;
  T y;
  T z;

  static constexpr auto zero() noexcept {
    return Vec<T, 3>{T(0), T(0), T(0)};
  }

  static constexpr auto all(T s) noexcept {
    return Vec<T, 3>{s, s, s};
  }

  static constexpr auto x_axis() noexcept {
    return Vec<T, 3>{T(1), T(0), T(0)};
  }

  static constexpr auto y_axis() noexcept {
    return Vec<T, 3>{T(0), T(1), T(0)};
  }

  static constexpr auto z_axis() noexcept {
    return Vec<T, 3>{T(0), T(0), T(1)};
  }

  Vec() = default;

  constexpr Vec(T x, T y, T z) noexcept
      : x{x}, y{y}, z{z} {}

  constexpr Vec(Vec<T, 2> xy, T z) noexcept
      : x{xy.x}, y{xy.y}, z{z} {}

  constexpr Vec(T x, Vec<T, 2> yz) noexcept
      : x{x}, y{yz.x}, z{yz.y} {}

  template <std::invocable<int> F>
  constexpr explicit Vec(F &&f) noexcept(noexcept(f(0)))
      : x{f(0)}, y{f(1)}, z{f(2)} {}

  template <typename U>
  constexpr explicit Vec(Vec<U, 3> const &v) noexcept
      : x{static_cast<T>(v.x)},
        y{static_cast<T>(v.y)},
        z{static_cast<T>(v.z)} {}

  constexpr T const &operator[](int n) const noexcept {
    assert(n >= 0 && n < 3);
    switch (n) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      std::unreachable();
    }
  }

  constexpr T &operator[](int n) noexcept {
    assert(n >= 0 && n < 3);
    switch (n) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      std::unreachable();
    }
  }

  constexpr Vec<T, 2> xy() const noexcept {
    return {x, y};
  }
};

template <typename T> struct Vec<T, 4> {
  T x;
  T y;
  T z;
  T w;

  static auto zero() {
    return Vec<T, 4>{T(0), T(0), T(0), T(0)};
  }

  static auto all(T s) {
    return Vec<T, 4>{s, s, s, s};
  }

  static constexpr auto x_axis() noexcept {
    return Vec<T, 4>{T(1), T(0), T(0), T(0)};
  }

  static constexpr auto y_axis() noexcept {
    return Vec<T, 4>{T(0), T(1), T(0), T(0)};
  }

  static constexpr auto z_axis() noexcept {
    return Vec<T, 4>{T(0), T(0), T(1), T(0)};
  }

  static constexpr auto w_axis() noexcept {
    return Vec<T, 4>{T(0), T(0), T(0), T(1)};
  }

  Vec() = default;

  constexpr Vec(T x, T y, T z, T w) noexcept
      : x{x}, y{y}, z{z}, w{w} {}

  constexpr Vec(Vec<T, 2> xy, Vec<T, 2> zw) noexcept
      : x{xy.x}, y{xy.y}, z{zw.x}, w{zw.y} {}

  constexpr Vec(Vec<T, 2> xy, T z, T w) noexcept
      : x{xy.x}, y{xy.y}, z{z}, w{w} {}

  constexpr Vec(T x, Vec<T, 2> yz, T w) noexcept
      : x{x}, y{yz.x}, z{yz.y}, w{w} {}

  constexpr Vec(T x, T y, Vec<T, 2> zw) noexcept
      : x{x}, y{y}, z{zw.x}, w{zw.y} {}

  constexpr Vec(Vec<T, 3> xyz, T w) noexcept
      : x{xyz.x}, y{xyz.y}, z{xyz.z}, w{w} {}

  constexpr Vec(T x, Vec<T, 3> yzw) noexcept
      : x{x}, y{yzw.x}, z{yzw.y}, w{yzw.z} {}

  template <typename F>
  constexpr explicit Vec(F &&f) noexcept(noexcept(f(0)))
      : x{f(0)}, y{f(1)}, z{f(2)}, w{f(3)} {}

  template <typename U>
  constexpr explicit Vec(Vec<U, 4> const &v) noexcept
      : x{static_cast<T>(v.x)},
        y{static_cast<T>(v.y)},
        z{static_cast<T>(v.z)},
        w{static_cast<T>(v.w)} {}

  constexpr T const &operator[](int n) const noexcept {
    assert(n >= 0 && n < 4);
    switch (n) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    case 3:
      return w;
    default:
      std::unreachable();
    }
  }

  constexpr T &operator[](int n) noexcept {
    assert(n >= 0 && n < 4);
    switch (n) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    case 3:
      return w;
    default:
      std::unreachable();
    }
  }

  constexpr Vec<T, 2> xy() const noexcept {
    return {x, y};
  }

  constexpr Vec<T, 3> xyz() const noexcept {
    return {x, y, z};
  }
};

template <typename T> using Vec2 = Vec<T, 2>;
template <typename T> using Vec3 = Vec<T, 3>;
template <typename T> using Vec4 = Vec<T, 4>;

using Vec2i = Vec2<std::int32_t>;
using Vec3i = Vec3<std::int32_t>;
using Vec4i = Vec4<std::int32_t>;
using Vec2u = Vec2<std::uint32_t>;
using Vec3u = Vec3<std::uint32_t>;
using Vec4u = Vec4<std::uint32_t>;
using Vec2f = Vec2<float>;
using Vec3f = Vec3<float>;
using Vec4f = Vec4<float>;
using Vec2d = Vec2<double>;
using Vec3d = Vec3<double>;
using Vec4d = Vec4<double>;
using Vec2i8 = Vec2<std::int8_t>;
using Vec3i8 = Vec3<std::int8_t>;
using Vec4i8 = Vec4<std::int8_t>;
using Vec2u8 = Vec2<std::uint8_t>;
using Vec3u8 = Vec3<std::uint8_t>;
using Vec4u8 = Vec4<std::uint8_t>;
using Vec2i16 = Vec2<std::int16_t>;
using Vec3i16 = Vec3<std::int16_t>;
using Vec4i16 = Vec4<std::int16_t>;
using Vec2u16 = Vec2<std::uint16_t>;
using Vec3u16 = Vec3<std::uint16_t>;
using Vec4u16 = Vec4<std::uint16_t>;
using Vec2i32 = Vec2<std::int32_t>;
using Vec3i32 = Vec3<std::int32_t>;
using Vec4i32 = Vec4<std::int32_t>;
using Vec2u32 = Vec2<std::uint32_t>;
using Vec3u32 = Vec3<std::uint32_t>;
using Vec4u32 = Vec4<std::uint32_t>;

static_assert(std::is_standard_layout_v<Vec2i>);
static_assert(offsetof(Vec2i, x) == 0);
static_assert(offsetof(Vec2i, y) == 4);
static_assert(sizeof(Vec2i) == 8);

static_assert(std::is_standard_layout_v<Vec3i>);
static_assert(offsetof(Vec3i, x) == 0);
static_assert(offsetof(Vec3i, y) == 4);
static_assert(offsetof(Vec3i, z) == 8);
static_assert(sizeof(Vec3i) == 12);

static_assert(std::is_standard_layout_v<Vec4i>);
static_assert(offsetof(Vec4i, x) == 0);
static_assert(offsetof(Vec4i, y) == 4);
static_assert(offsetof(Vec4i, z) == 8);
static_assert(offsetof(Vec4i, w) == 12);
static_assert(sizeof(Vec4i) == 16);

static_assert(std::is_standard_layout_v<Vec2u>);
static_assert(offsetof(Vec2u, x) == 0);
static_assert(offsetof(Vec2u, y) == 4);
static_assert(sizeof(Vec2u) == 8);

static_assert(std::is_standard_layout_v<Vec3u>);
static_assert(offsetof(Vec3u, x) == 0);
static_assert(offsetof(Vec3u, y) == 4);
static_assert(offsetof(Vec3u, z) == 8);
static_assert(sizeof(Vec3u) == 12);

static_assert(std::is_standard_layout_v<Vec4u>);
static_assert(offsetof(Vec4u, x) == 0);
static_assert(offsetof(Vec4u, y) == 4);
static_assert(offsetof(Vec4u, z) == 8);
static_assert(offsetof(Vec4u, w) == 12);
static_assert(sizeof(Vec4u) == 16);

static_assert(std::is_standard_layout_v<Vec2f>);
static_assert(offsetof(Vec2f, x) == 0);
static_assert(offsetof(Vec2f, y) == 4);
static_assert(sizeof(Vec2f) == 8);

static_assert(std::is_standard_layout_v<Vec3f>);
static_assert(offsetof(Vec3f, x) == 0);
static_assert(offsetof(Vec3f, y) == 4);
static_assert(offsetof(Vec3f, z) == 8);
static_assert(sizeof(Vec3f) == 12);

static_assert(std::is_standard_layout_v<Vec4f>);
static_assert(offsetof(Vec4f, x) == 0);
static_assert(offsetof(Vec4f, y) == 4);
static_assert(offsetof(Vec4f, z) == 8);
static_assert(offsetof(Vec4f, w) == 12);
static_assert(sizeof(Vec4f) == 16);

static_assert(std::is_standard_layout_v<Vec2d>);
static_assert(offsetof(Vec2d, x) == 0);
static_assert(offsetof(Vec2d, y) == 8);
static_assert(sizeof(Vec2d) == 16);

static_assert(std::is_standard_layout_v<Vec3d>);
static_assert(offsetof(Vec3d, x) == 0);
static_assert(offsetof(Vec3d, y) == 8);
static_assert(offsetof(Vec3d, z) == 16);
static_assert(sizeof(Vec3d) == 24);

static_assert(std::is_standard_layout_v<Vec4d>);
static_assert(offsetof(Vec4d, x) == 0);
static_assert(offsetof(Vec4d, y) == 8);
static_assert(offsetof(Vec4d, z) == 16);
static_assert(offsetof(Vec4d, w) == 24);
static_assert(sizeof(Vec4d) == 32);

static_assert(std::is_standard_layout_v<Vec2i8>);
static_assert(offsetof(Vec2i8, x) == 0);
static_assert(offsetof(Vec2i8, y) == 1);
static_assert(sizeof(Vec2i8) == 2);

static_assert(std::is_standard_layout_v<Vec3i8>);
static_assert(offsetof(Vec3i8, x) == 0);
static_assert(offsetof(Vec3i8, y) == 1);
static_assert(offsetof(Vec3i8, z) == 2);
static_assert(sizeof(Vec3i8) == 3);

static_assert(std::is_standard_layout_v<Vec4i8>);
static_assert(offsetof(Vec4i8, x) == 0);
static_assert(offsetof(Vec4i8, y) == 1);
static_assert(offsetof(Vec4i8, z) == 2);
static_assert(offsetof(Vec4i8, w) == 3);
static_assert(sizeof(Vec4i8) == 4);

static_assert(std::is_standard_layout_v<Vec2u8>);
static_assert(offsetof(Vec2u8, x) == 0);
static_assert(offsetof(Vec2u8, y) == 1);
static_assert(sizeof(Vec2u8) == 2);

static_assert(std::is_standard_layout_v<Vec3u8>);
static_assert(offsetof(Vec3u8, x) == 0);
static_assert(offsetof(Vec3u8, y) == 1);
static_assert(offsetof(Vec3u8, z) == 2);
static_assert(sizeof(Vec3u8) == 3);

static_assert(std::is_standard_layout_v<Vec4u8>);
static_assert(offsetof(Vec4u8, x) == 0);
static_assert(offsetof(Vec4u8, y) == 1);
static_assert(offsetof(Vec4u8, z) == 2);
static_assert(offsetof(Vec4u8, w) == 3);
static_assert(sizeof(Vec4u8) == 4);

static_assert(std::is_standard_layout_v<Vec2i16>);
static_assert(offsetof(Vec2i16, x) == 0);
static_assert(offsetof(Vec2i16, y) == 2);
static_assert(sizeof(Vec2i16) == 4);

static_assert(std::is_standard_layout_v<Vec3i16>);
static_assert(offsetof(Vec3i16, x) == 0);
static_assert(offsetof(Vec3i16, y) == 2);
static_assert(offsetof(Vec3i16, z) == 4);
static_assert(sizeof(Vec3i16) == 6);

static_assert(std::is_standard_layout_v<Vec4i16>);
static_assert(offsetof(Vec4i16, x) == 0);
static_assert(offsetof(Vec4i16, y) == 2);
static_assert(offsetof(Vec4i16, z) == 4);
static_assert(offsetof(Vec4i16, w) == 6);
static_assert(sizeof(Vec4i16) == 8);

static_assert(std::is_standard_layout_v<Vec2u16>);
static_assert(offsetof(Vec2u16, x) == 0);
static_assert(offsetof(Vec2u16, y) == 2);
static_assert(sizeof(Vec2u16) == 4);

static_assert(std::is_standard_layout_v<Vec3u16>);
static_assert(offsetof(Vec3u16, x) == 0);
static_assert(offsetof(Vec3u16, y) == 2);
static_assert(offsetof(Vec3u16, z) == 4);
static_assert(sizeof(Vec3u16) == 6);

static_assert(std::is_standard_layout_v<Vec4u16>);
static_assert(offsetof(Vec4u16, x) == 0);
static_assert(offsetof(Vec4u16, y) == 2);
static_assert(offsetof(Vec4u16, z) == 4);
static_assert(offsetof(Vec4u16, w) == 6);
static_assert(sizeof(Vec4u16) == 8);

static_assert(std::is_standard_layout_v<Vec2i32>);
static_assert(offsetof(Vec2i32, x) == 0);
static_assert(offsetof(Vec2i32, y) == 4);
static_assert(sizeof(Vec2i32) == 8);

static_assert(std::is_standard_layout_v<Vec3i32>);
static_assert(offsetof(Vec3i32, x) == 0);
static_assert(offsetof(Vec3i32, y) == 4);
static_assert(offsetof(Vec3i32, z) == 8);
static_assert(sizeof(Vec3i32) == 12);

static_assert(std::is_standard_layout_v<Vec4i32>);
static_assert(offsetof(Vec4i32, x) == 0);
static_assert(offsetof(Vec4i32, y) == 4);
static_assert(offsetof(Vec4i32, z) == 8);
static_assert(offsetof(Vec4i32, w) == 12);
static_assert(sizeof(Vec4i32) == 16);

static_assert(std::is_standard_layout_v<Vec2u32>);
static_assert(offsetof(Vec2u32, x) == 0);
static_assert(offsetof(Vec2u32, y) == 4);
static_assert(sizeof(Vec2u32) == 8);

static_assert(std::is_standard_layout_v<Vec3u32>);
static_assert(offsetof(Vec3u32, x) == 0);
static_assert(offsetof(Vec3u32, y) == 4);
static_assert(offsetof(Vec3u32, z) == 8);
static_assert(sizeof(Vec3u32) == 12);

static_assert(std::is_standard_layout_v<Vec4u32>);
static_assert(offsetof(Vec4u32, x) == 0);
static_assert(offsetof(Vec4u32, y) == 4);
static_assert(offsetof(Vec4u32, z) == 8);
static_assert(offsetof(Vec4u32, w) == 12);
static_assert(sizeof(Vec4u32) == 16);

template <typename T, int N>
constexpr bool operator==(Vec<T, N> const &u, Vec<T, N> const &v) noexcept {
  for (int i = 0; i < N; ++i) {
    if (u[i] != v[i]) {
      return false;
    }
  }
  return true;
}

template <typename T, int N>
constexpr auto operator+(Vec<T, N> const &v) noexcept {
  return v;
}

template <typename T, int N>
constexpr auto operator-(Vec<T, N> const &v) noexcept {
  return Vec<T, N>{[&](int i) { return -v[i]; }};
}

template <typename T, int N>
constexpr auto operator+(Vec<T, N> const &u, Vec<T, N> const &v) noexcept {
  return Vec<T, N>{[&](int i) { return u[i] + v[i]; }};
}

template <typename T, int N>
constexpr auto operator-(Vec<T, N> const &u, Vec<T, N> const &v) noexcept {
  return Vec<T, N>{[&](int i) { return u[i] - v[i]; }};
}

template <typename T, int N>
constexpr auto operator*(T s, Vec<T, N> const &v) noexcept {
  return Vec<T, N>{[&](int i) { return s * v[i]; }};
}

template <typename T, int N>
constexpr auto operator*(Vec<T, N> const &v, T s) noexcept {
  return Vec<T, N>{[&](int i) { return v[i] * s; }};
}

template <typename T, int N>
constexpr auto operator/(Vec<T, N> const &v, T s) noexcept {
  if constexpr (std::is_floating_point_v<T>) {
    return v * (1 / s);
  } else {
    return Vec<T, N>{[&](int i) { return v[i] / s; }};
  }
}

template <typename T, int N>
constexpr auto &operator+=(Vec<T, N> &u, Vec<T, N> const &v) noexcept {
  return u = (u + v);
}

template <typename T, int N>
constexpr auto &operator-=(Vec<T, N> &u, Vec<T, N> const &v) noexcept {
  return u = (u - v);
}

template <typename T, int N>
constexpr auto &operator*=(Vec<T, N> &v, T s) noexcept {
  return v = (v * s);
}

template <typename T, int N>
constexpr auto &operator/=(Vec<T, N> &v, T s) noexcept {
  return v = (v / s);
}

template <typename T, int N>
constexpr auto length_squared(Vec<T, N> const &v) noexcept {
  auto retval = T(0);
  for (int i = 0; i < N; ++i) {
    retval += v[i] * v[i];
  }
  return retval;
}

template <typename T, int N>
constexpr auto length(Vec<T, N> const &v) noexcept {
  return std::sqrt(length_squared(v));
}

template <typename T, int N>
constexpr auto normalize(Vec<T, N> const &v) noexcept {
  return v / length(v);
}

template <typename T, int N>
constexpr auto dot(Vec<T, N> const &a, Vec<T, N> const &b) noexcept {
  auto retval = T(0);
  for (int i = 0; i < N; ++i) {
    retval += a[i] * b[i];
  }
  return retval;
}

template <typename T>
constexpr auto cross(Vec<T, 3> const &a, Vec<T, 3> const &b) noexcept {
  return Vec<T, 3>{
      a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

template <typename T, int N>
constexpr auto proj(Vec<T, N> const &u, Vec<T, N> const &d) noexcept {
  return dot(u, d) / length_squared(d) * d;
}

template <typename T, int N>
constexpr auto proj_unit(Vec<T, N> const &u, Vec<T, N> const &d) noexcept {
  return dot(u, d) * d;
}

template <typename T, int N>
constexpr auto perp(Vec<T, N> const &u, Vec<T, N> const &d) noexcept {
  return u - proj(u, d);
}

template <typename T, int N>
constexpr auto perp_unit(Vec<T, N> const &u, Vec<T, N> const &d) noexcept {
  return u - proj_unit(u, d);
}

template <typename T, int N>
constexpr auto min(Vec<T, N> const &a, Vec<T, N> const &b) noexcept {
  return Vec<T, N>{[&](int i) { return min(a[i], b[i]); }};
}

template <typename T, int N>
constexpr auto max(Vec<T, N> const &a, Vec<T, N> const &b) noexcept {
  return Vec<T, N>{[&](int i) { return max(a[i], b[i]); }};
}

template <typename T, int N>
constexpr auto
clamp(Vec<T, N> const &v, Vec<T, N> const &lo, Vec<T, N> const &hi) noexcept {
  return Vec<T, N>{[&](int i) { return clamp(v[i], lo[i], hi[i]); }};
}

template <typename T, int N> constexpr auto abs(Vec<T, N> const &v) noexcept {
  return Vec<T, N>{[&](int i) { return abs(v[i]); }};
}
} // namespace marlon

#endif
