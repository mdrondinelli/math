#ifndef MARLON_MATH_MAT_H
#define MARLON_MATH_MAT_H

#include <concepts>

#include "quat.h"
#include "vec.h"

namespace marlon::math {
template <typename T, int N> class Rvec;

template <typename T> class Rvec<T, 2> {
public:
  static constexpr auto zero() noexcept {
    return Rvec<T, 2>{T(0), T(0)};
  }

  Rvec() = default;

  constexpr Rvec(T x, T y) noexcept
      : _components{x, y} {}

  template <typename F>
  constexpr explicit Rvec(F &&f) noexcept(noexcept(f(0)))
      : _components{f(0), f(1)} {}

  template <typename U>
  constexpr explicit Rvec(Rvec<U, 2> const &other) noexcept
      : _components{
            static_cast<T>(other[0]),
            static_cast<T>(other[1]),
        } {}

  constexpr auto const &operator[](int n) const noexcept {
    return _components[n];
  }

  constexpr auto &operator[](int n) noexcept {
    return _components[n];
  }

private:
  T _components[2];
};

template <typename T> class Rvec<T, 3> {
public:
  static constexpr auto zero() noexcept {
    return Rvec<T, 3>{T(0), T(0), T(0)};
  }

  Rvec() = default;

  constexpr Rvec(T x, T y, T z) noexcept
      : _components{x, y, z} {}

  constexpr Rvec(Rvec<T, 2> xy, T z) noexcept
      : _components{xy[0], xy[1], z} {}

  constexpr Rvec(T x, Rvec<T, 2> yz) noexcept
      : _components{x, yz[0], yz[1]} {}

  template <typename F>
  constexpr explicit Rvec(F &&f) noexcept(noexcept(f(0)))
      : _components{f(0), f(1), f(2)} {}

  template <typename U>
  constexpr explicit Rvec(Rvec<U, 3> const &other) noexcept
      : _components{
            static_cast<T>(other[0]),
            static_cast<T>(other[1]),
            static_cast<T>(other[2]),
        } {}

  constexpr auto const &operator[](int n) const noexcept {
    return _components[n];
  }

  constexpr auto &operator[](int n) noexcept {
    return _components[n];
  }

private:
  T _components[3];
};

template <typename T> class Rvec<T, 4> {
public:
  static constexpr auto zero() noexcept {
    return Rvec<T, 4>{T(0), T(0), T(0), T(0)};
  }

  Rvec() = default;

  constexpr Rvec(T x, T y, T z, T w) noexcept
      : _components{x, y, z, w} {}

  constexpr Rvec(Rvec<T, 2> xy, Rvec<T, 2> zw) noexcept
      : _components{xy[0], xy[1], zw[0], zw[1]} {}

  constexpr Rvec(Rvec<T, 2> xy, T z, T w) noexcept
      : _components{xy[0], xy[1], z, w} {}

  constexpr Rvec(T x, Rvec<T, 2> yz, T w) noexcept
      : _components{x, yz[0], yz[1], w} {}

  constexpr Rvec(T x, T y, Rvec<T, 2> zw) noexcept
      : _components{x, y, zw[0], zw[1]} {}

  constexpr Rvec(Rvec<T, 3> xyz, T w) noexcept
      : _components{xyz[0], xyz[1], xyz[2], w} {}

  constexpr Rvec(T x, Rvec<T, 3> yzw) noexcept
      : _components{x, yzw[0], yzw[1], yzw[2]} {}

  template <typename F>
  constexpr explicit Rvec(F &&f) noexcept(noexcept(f(0)))
      : _components{f(0), f(1), f(2), f(3)} {}

  template <typename U>
  constexpr explicit Rvec(Rvec<U, 4> const &other) noexcept
      : _components{
            static_cast<T>(other[0]),
            static_cast<T>(other[1]),
            static_cast<T>(other[2]),
            static_cast<T>(other[3]),
        } {}

  constexpr auto const &operator[](int n) const noexcept {
    return _components[n];
  }

  constexpr auto &operator[](int n) noexcept {
    return _components[n];
  }

private:
  T _components[4];
};

template <typename T, int N, int M> class Mat;

template <typename T, int M> class Mat<T, 2, M> {
public:
  static auto zero() {
    return Mat<T, 2, M>{
        Rvec<T, M>::zero(),
        Rvec<T, M>::zero(),
    };
  }

  static auto identity() {
    static_assert(M == 2);
    return Mat<T, 2, 2>{
        {T(1), T(0)},
        {T(0), T(1)},
    };
  }

  Mat() = default;

  constexpr Mat(Rvec<T, M> const &row0, Rvec<T, M> const &row1) noexcept
      : rows{row0, row1} {}

  template <std::invocable<int> F>
  constexpr explicit Mat(F &&f) noexcept(noexcept(f(0)))
      : rows{f(0), f(1)} {}

  template <typename U>
  constexpr explicit Mat(Mat<U, 2, M> const &m) noexcept
      : rows{
            static_cast<Rvec<T, M>>(m[0]),
            static_cast<Rvec<T, M>>(m[1]),
        } {}

  constexpr auto const &operator[](int n) const noexcept {
    return rows[n];
  }

  constexpr auto &operator[](int n) noexcept {
    return rows[n];
  }

private:
  Rvec<T, M> rows[2];
};

template <typename T, int M> class Mat<T, 3, M> {
public:
  static constexpr auto zero() noexcept {
    return Mat<T, 3, M>{
        Rvec<T, M>::zero(),
        Rvec<T, M>::zero(),
        Rvec<T, M>::zero(),
    };
  }

  static constexpr auto identity() noexcept {
    static_assert(M == 3 || M == 4);
    if constexpr (M == 3) {
      return Mat<T, 3, 3>{
          Rvec<T, 3>{T(1), T(0), T(0)},
          Rvec<T, 3>{T(0), T(1), T(0)},
          Rvec<T, 3>{T(0), T(0), T(1)},
      };
    } else {
      return Mat<T, 3, 4>{
          Rvec<T, 4>{T(1), T(0), T(0), T(0)},
          Rvec<T, 4>{T(0), T(1), T(0), T(0)},
          Rvec<T, 4>{T(0), T(0), T(1), T(0)},
      };
    }
  }

  static constexpr auto translation(math::Vec3<T> const &t) noexcept {
    static_assert(M == 4);
    return Mat<T, 3, 4>{
        {T(1), T(0), T(0), t.x},
        {T(0), T(1), T(0), t.y},
        {T(0), T(0), T(1), t.z},
    };
  }

  static constexpr auto rotation(Quat<T> const &r) noexcept {
    static_assert(M == 3 || M == 4);
    auto const m00 = T(1) - T(2) * r.v.y * r.v.y - T(2) * r.v.z * r.v.z;
    auto const m01 = T(2) * r.v.x * r.v.y - T(2) * r.w * r.v.z;
    auto const m02 = T(2) * r.v.x * r.v.z + T(2) * r.w * r.v.y;
    auto const m10 = T(2) * r.v.x * r.v.y + T(2) * r.w * r.v.z;
    auto const m11 = T(1) - T(2) * r.v.x * r.v.x - T(2) * r.v.z * r.v.z;
    auto const m12 = T(2) * r.v.y * r.v.z - T(2) * r.w * r.v.x;
    auto const m20 = T(2) * r.v.x * r.v.z - T(2) * r.w * r.v.y;
    auto const m21 = T(2) * r.v.y * r.v.z + T(2) * r.w * r.v.x;
    auto const m22 = T(1) - T(2) * r.v.x * r.v.x - T(2) * r.v.y * r.v.y;
    if constexpr (M == 3) {
      return Mat<T, 3, 3>{
          {m00, m01, m02},
          {m10, m11, m12},
          {m20, m21, m22},
      };
    } else {
      return Mat<T, 3, 4>{
          {m00, m01, m02, T(0)},
          {m10, m11, m12, T(0)},
          {m20, m21, m22, T(0)},
      };
    }
  }

  static constexpr auto scale(T s) noexcept {
    static_assert(M == 3 || M == 4);
    if constexpr (M == 3) {
      return Mat<T, 3, 3>{
          {s, T(0), T(0)},
          {T(0), s, T(0)},
          {T(0), T(0), s},
      };
    } else {
      return Mat<T, 3, 4>{
          {s, T(0), T(0), T(0)},
          {T(0), s, T(0), T(0)},
          {T(0), T(0), s, T(0)},
      };
    }
  }

  static constexpr auto rigid(Vec3<T> const &t, Quat<T> const &r) noexcept {
    static_assert(M == 4);
    auto result = rotation(r);
    result[0][3] = t.x;
    result[1][3] = t.y;
    result[2][3] = t.z;
    return result;
  }

  static constexpr auto trs(Vec3<T> const &t, Quat<T> const &r, T s) noexcept {
    static_assert(M == 4);
    auto result = rigid(t, r);
    for (auto i = 0; i < 3; ++i) {
      for (auto j = 0; j < 3; ++j) {
        result[i][j] *= s;
      }
    }
    return result;
  }

  static constexpr auto
  trs(Vec3<T> const &t, Quat<T> const &r, Vec3<T> const &s) noexcept {
    static_assert(M == 4);
    auto result = rigid(t, r);
    for (auto i = 0; i < 3; ++i) {
      for (auto j = 0; j < 3; ++j) {
        result[i][j] *= s[j];
      }
    }
    return result;
  }

  static constexpr auto orthographic(T l, T r, T b, T t, T n, T f) noexcept {
    static_assert(M == 4);
    return Mat<T, 3, 4>{
        {T(2) / (r - l), T(0), T(0), -(r + l) / (r - l)},
        {T(0), T(-2) / (t - b), T(0), (t + b) / (t - b)},
        {T(0), T(0), T(1) / (n - f), -f / (n - f)},
    };
  }

  Mat() = default;

  constexpr Mat(Rvec<T, M> const &row0,
                Rvec<T, M> const &row1,
                Rvec<T, M> const &row2) noexcept
      : rows{row0, row1, row2} {}

  constexpr Mat(Mat<T, 2, M> const &row0, Rvec<T, M> const &row2) noexcept
      : rows{row0[0], row0[1], row2} {}

  constexpr Mat(Rvec<T, M> const &row0, Mat<T, 2, M> const &row1) noexcept
      : rows{row0, row1[0], row1[1]} {}

  template <std::invocable<int> F>
  constexpr explicit Mat(F &&f) noexcept(noexcept(f(0)))
      : rows{f(0), f(1), f(2)} {}

  template <typename U>
  constexpr explicit Mat(Mat<U, 3, M> const &m) noexcept
      : rows{
            static_cast<Rvec<T, M>>(m[0]),
            static_cast<Rvec<T, M>>(m[1]),
            static_cast<Rvec<T, M>>(m[2]),
        } {}

  constexpr auto const &operator[](int n) const noexcept {
    return rows[n];
  }

  constexpr auto &operator[](int n) noexcept {
    return rows[n];
  }

private:
  Rvec<T, M> rows[3];
};

template <typename T, int M> class Mat<T, 4, M> {
public:
  static constexpr auto zero() {
    return Mat<T, 4, M>{
        Rvec<T, M>::zero(),
        Rvec<T, M>::zero(),
        Rvec<T, M>::zero(),
        Rvec<T, M>::zero(),
    };
  }

  static constexpr auto identity() {
    static_assert(M == 4);
    return Mat<T, 4, 4>{
        {T(1), T(0), T(0), T(0)},
        {T(0), T(1), T(0), T(0)},
        {T(0), T(0), T(1), T(0)},
        {T(0), T(0), T(0), T(1)},
    };
  }

  static constexpr auto translation(math::Vec3<T> const &t) noexcept {
    static_assert(M == 4);
    return Mat<T, 4, 4>{Mat<T, 3, 4>::translation(t), {T(0), T(0), T(0), T(1)}};
  }

  static constexpr auto rotation(Quat<T> const &r) noexcept {
    static_assert(M == 4);
    return Mat<T, 4, 4>{Mat<T, 3, 4>::rotation(r), {T(0), T(0), T(0), T(1)}};
  }

  static constexpr auto scale(T s) noexcept {
    static_assert(M == 4);
    return Mat<T, 4, 4>{Mat<T, 3, 4>::scale(s), {T(0), T(0), T(0), T(1)}};
  }

  static constexpr auto rigid(Vec3<T> const &t, Quat<T> const &r) noexcept {
    static_assert(M == 4);
    return Mat<T, 4, 4>{Mat<T, 3, 4>::rigid(t, r), {T(0), T(0), T(0), T(1)}};
  }

  static constexpr auto trs(Vec3<T> const &t, Quat<T> const &r, T s) noexcept {
    static_assert(M == 4);
    return Mat<T, 4, 4>{Mat<T, 3, 4>::trs(t, r, s), {T(0), T(0), T(0), T(1)}};
  }

  static constexpr auto
  trs(Vec3<T> const &t, Quat<T> const &r, Vec3<T> const &s) noexcept {
    static_assert(M == 4);
    return Mat<T, 4, 4>{Mat<T, 3, 4>::trs(t, r, s), {T(0), T(0), T(0), T(1)}};
  }

  static constexpr auto orthographic(T l, T r, T b, T t, T n, T f) noexcept {
    static_assert(M == 4);
    return Mat<T, 4, 4>{
        Mat<T, 3, 4>::orthographic(l, r, b, t, n, f),
        {T(0), T(0), T(0), T(1)},
    };
  }

  Mat() = default;

  constexpr Mat(Rvec<T, M> const &row0,
                Rvec<T, M> const &row1,
                Rvec<T, M> const &row2,
                Rvec<T, M> const &row3) noexcept
      : rows{row0, row1, row2, row3} {}

  constexpr Mat(Mat<T, 2, M> const &row0,
                Rvec<T, M> const &row2,
                Rvec<T, M> const &row3) noexcept
      : rows{row0[0], row0[1], row2, row3} {}

  constexpr Mat(Rvec<T, M> const &row0,
                Mat<T, 2, M> const &row1,
                Rvec<T, M> const &row3) noexcept
      : rows{row0, row1[0], row1[1], row3} {}

  constexpr Mat(Rvec<T, M> const &row0,
                Rvec<T, M> const &row1,
                Mat<T, 2, M> const &row2) noexcept
      : rows{row0, row1, row2[0], row2[1]} {}

  constexpr Mat(Mat<T, 3, M> const &row0, Rvec<T, M> const &row3) noexcept
      : rows{row0[0], row0[1], row0[2], row3} {}

  constexpr Mat(Rvec<T, M> const &row0, Mat<T, 3, M> const &row1) noexcept
      : rows{row0, row1[0], row1[1], row1[2]} {}

  template <typename F>
  constexpr explicit Mat(F &&f) noexcept(noexcept(f(0)))
      : rows{f(0), f(1), f(2), f(3)} {}

  template <typename U>
  constexpr explicit Mat(Mat<U, 4, M> const &m) noexcept
      : rows{static_cast<Rvec<T, M>>(m[0]),
             static_cast<Rvec<T, M>>(m[1]),
             static_cast<Rvec<T, M>>(m[2]),
             static_cast<Rvec<T, M>>(m[3])} {}

  constexpr auto const &operator[](int n) const noexcept {
    return rows[n];
  }

  constexpr auto &operator[](int n) noexcept {
    return rows[n];
  }

private:
  Rvec<T, M> rows[4];
};

template <typename T> using Rvec2 = Rvec<T, 2>;
template <typename T> using Rvec3 = Rvec<T, 3>;
template <typename T> using Rvec4 = Rvec<T, 4>;
template <typename T> using Mat2x2 = Mat<T, 2, 2>;
template <typename T> using Mat2x3 = Mat<T, 2, 3>;
template <typename T> using Mat2x4 = Mat<T, 2, 4>;
template <typename T> using Mat3x2 = Mat<T, 3, 2>;
template <typename T> using Mat3x3 = Mat<T, 3, 3>;
template <typename T> using Mat3x4 = Mat<T, 3, 4>;
template <typename T> using Mat4x2 = Mat<T, 4, 2>;
template <typename T> using Mat4x3 = Mat<T, 4, 3>;
template <typename T> using Mat4x4 = Mat<T, 4, 4>;
using Rvec2i = Rvec2<std::int32_t>;
using Rvec3i = Rvec2<std::int32_t>;
using Rvec4i = Rvec2<std::int32_t>;
using Rvec2f = Rvec2<float>;
using Rvec3f = Rvec2<float>;
using Rvec4f = Rvec2<float>;
using Rvec2d = Rvec2<double>;
using Rvec3d = Rvec2<double>;
using Rvec4d = Rvec2<double>;
using Mat2x2i = Mat<std::int32_t, 2, 2>;
using Mat2x3i = Mat<std::int32_t, 2, 3>;
using Mat2x4i = Mat<std::int32_t, 2, 4>;
using Mat3x2i = Mat<std::int32_t, 3, 2>;
using Mat3x3i = Mat<std::int32_t, 3, 3>;
using Mat3x4i = Mat<std::int32_t, 3, 4>;
using Mat4x2i = Mat<std::int32_t, 4, 2>;
using Mat4x3i = Mat<std::int32_t, 4, 3>;
using Mat4x4i = Mat<std::int32_t, 4, 4>;
using Mat2x2f = Mat<float, 2, 2>;
using Mat2x3f = Mat<float, 2, 3>;
using Mat2x4f = Mat<float, 2, 4>;
using Mat3x2f = Mat<float, 3, 2>;
using Mat3x3f = Mat<float, 3, 3>;
using Mat3x4f = Mat<float, 3, 4>;
using Mat4x2f = Mat<float, 4, 2>;
using Mat4x3f = Mat<float, 4, 3>;
using Mat4x4f = Mat<float, 4, 4>;
using Mat2x2d = Mat<double, 2, 2>;
using Mat2x3d = Mat<double, 2, 3>;
using Mat2x4d = Mat<double, 2, 4>;
using Mat3x2d = Mat<double, 3, 2>;
using Mat3x3d = Mat<double, 3, 3>;
using Mat3x4d = Mat<double, 3, 4>;
using Mat4x2d = Mat<double, 4, 2>;
using Mat4x3d = Mat<double, 4, 3>;
using Mat4x4d = Mat<double, 4, 4>;

template <typename T, int N>
constexpr bool operator==(Rvec<T, N> const &a, Rvec<T, N> const &b) noexcept {
  for (auto i = 0; i < N; ++i) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

template <typename T, int N>
constexpr Rvec<T, N> operator*(T s, Rvec<T, N> const &v) noexcept {
  return Rvec<T, N>{[&](int i) { return s * v[i]; }};
}

template <typename T, int N>
constexpr Rvec<T, N> operator*(Rvec<T, N> const &v, T s) noexcept {
  return s * v;
}

template <typename T, int N>
constexpr Rvec<T, N> &operator*=(Rvec<T, N> &v, T s) noexcept {
  return v = v * s;
}

template <typename T, int N>
constexpr Rvec<T, N> operator/(Rvec<T, N> const &v, T s) noexcept {
  if constexpr (std::is_floating_point_v<T>) {
    return v * (T(1) / s);
  } else {
    return Rvec<T, N>{[&](int i) { return v[i] / s; }};
  }
}

template <typename T, int N>
constexpr Rvec<T, N> &operator/=(Rvec<T, N> &v, T s) noexcept {
  return v = v / s;
}

template <typename T, int N>
constexpr T operator*(Rvec<T, N> const &a, Vec<T, N> const &b) noexcept {
  auto retval = T(0);
  for (auto i = 0; i < N; ++i) {
    retval += a[i] * b[i];
  }
  return retval;
}

template <typename T, int N>
constexpr Rvec<T, N> abs(Rvec<T, N> const &v) noexcept {
  return Rvec<T, N>{[&](int i) { return std::abs(v[i]); }};
}

template <typename T, int N>
constexpr Rvec<T, N> transpose(Vec<T, N> const &v) noexcept {
  return Rvec<T, N>{[&](int i) { return v[i]; }};
}

template <typename T, int N>
constexpr Vec<T, N> transpose(Rvec<T, N> const &v) noexcept {
  return Vec<T, N>{[&](int i) { return v[i]; }};
}

template <typename T, int N, int M>
constexpr bool operator==(Mat<T, N, M> const &a,
                          Mat<T, N, M> const &b) noexcept {
  for (int i = 0; i < N; ++i) {
    if (a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

template <typename T, int N, int M>
constexpr Mat<T, N, M> &operator*=(Mat<T, N, M> &a,
                                   Mat<T, M, M> const &b) noexcept {
  return a = a * b;
}

template <typename T, int N, int M>
constexpr Mat<T, N, M> operator*(T s, Mat<T, N, M> const &m) noexcept {
  return Mat<T, N, M>{[&](int i) { return s * m[i]; }};
}

template <typename T, int N, int M>
constexpr Mat<T, N, M> operator*(Mat<T, N, M> const &m, T s) noexcept {
  return Mat<T, N, M>{[&](int i) { return m[i] * s; }};
}

template <typename T, int N, int M>
constexpr Mat<T, N, M> &operator*=(Mat<T, N, M> &a, T s) noexcept {
  return a = a * s;
}

template <typename T, int N, int M>
constexpr Rvec<T, M> operator*(Rvec<T, N> const &v,
                               Mat<T, N, M> const &m) noexcept {
  return Rvec<T, M>{[&](int j) {
    auto retval = T(0);
    for (int i = 0; i < N; ++i) {
      retval += v[i] * m[i][j];
    }
    return retval;
  }};
}

template <typename T, int N>
constexpr Rvec<T, N> &operator*=(Rvec<T, N> &v,
                                 Mat<T, N, N> const &m) noexcept {
  return v = v * m;
}

template <typename T, int N, int M>
constexpr Vec<T, N> operator*(Mat<T, N, M> const &m,
                              Vec<T, M> const &v) noexcept {
  return Vec<T, N>{[&](int i) {
    auto retval = T(0);
    for (int j = 0; j < M; ++j) {
      retval += m[i][j] * v[j];
    }
    return retval;
  }};
}

template <typename T, int N, int M>
constexpr Mat<T, N, M> operator/(Mat<T, N, M> const &m, T s) noexcept {
  if constexpr (std::is_floating_point_v<T>) {
    return m * (1 / s);
  } else {
    return Mat<T, N, M>{[&](int i) { return m[i] / s; }};
  };
}

template <typename T, int N, int M>
constexpr Mat<T, N, M> &operator/=(Mat<T, N, M> &m, T s) noexcept {
  return m = m / s;
}

template <typename T, int N1, int N2, int N3>
constexpr Mat<T, N1, N3> operator*(Mat<T, N1, N2> const &a,
                                   Mat<T, N2, N3> const &b) noexcept {
  auto retval = Mat<T, N1, N3>::zero();
  for (auto i = 0; i < N1; ++i) {
    for (auto j = 0; j < N3; ++j) {
      for (auto k = 0; k < N2; ++k) {
        retval[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return retval;
}

template <typename T, int N, int M>
constexpr Rvec<T, M> row(Mat<T, N, M> const &m, int i) noexcept {
  return m[i];
}

template <typename T, int N, int M>
constexpr Vec<T, N> column(Mat<T, N, M> const &m, int j) noexcept {
  return Vec<T, N>{[&](int i) { return m[i][j]; }};
}

template <typename T, int N, int M>
constexpr Mat<T, N, M> abs(math::Mat<T, N, M> const &m) noexcept {
  auto retval = Mat<T, N, M>::zero();
  for (auto i = 0; i < N; ++i) {
    retval[i] = abs(m[i]);
  }
  return retval;
}

template <typename T, int N, int M>
constexpr Mat<T, M, N> transpose(math::Mat<T, N, M> const &m) noexcept {
  auto retval = Mat<T, M, N>::zero();
  for (auto i = 0; i < M; ++i) {
    for (auto j = 0; j < N; ++j) {
      retval[i][j] = m[j][i];
    }
  }
  return retval;
}

template <typename T>
constexpr T determinant(math::Mat<T, 2, 2> const &m) noexcept {
  return m[0][0] * m[1][1] - m[0][1] * m[1][0];
}

template <typename T>
constexpr T determinant(math::Mat<T, 3, 3> const &m) noexcept {
  return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
         m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
         m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

template <typename T>
constexpr T determinant(math::Mat<T, 4, 4> const &m) noexcept {
  return m[0][0] * (m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) +
                    m[1][2] * (m[2][3] * m[3][1] - m[2][1] * m[3][3]) +
                    m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1])) -
         m[0][1] * (m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) +
                    m[1][2] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) +
                    m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0])) +
         m[0][2] * (m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) +
                    m[1][1] * (m[2][3] * m[3][0] - m[2][0] * m[3][3]) +
                    m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0])) -
         m[0][3] * (m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) +
                    m[1][1] * (m[2][2] * m[3][0] - m[2][0] * m[3][2]) +
                    m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0]));
}

template <typename T>
constexpr Mat<T, 2, 2> cofactors(math::Mat<T, 2, 2> const &m) noexcept {
  return {{m[1][1], -m[1][0]}, {-m[0][1], m[0][0]}};
}

template <typename T>
constexpr Mat<T, 3, 3> cofactors(math::Mat<T, 3, 3> const &m) noexcept {
  return {{determinant(Mat<T, 2, 2>{{m[1][1], m[1][2]}, {m[2][1], m[2][2]}}),
           -determinant(Mat<T, 2, 2>{{m[1][0], m[1][2]}, {m[2][0], m[2][2]}}),
           determinant(Mat<T, 2, 2>{{m[1][0], m[1][1]}, {m[2][0], m[2][1]}})},
          {-determinant(Mat<T, 2, 2>{{m[0][1], m[0][2]}, {m[2][1], m[2][2]}}),
           determinant(Mat<T, 2, 2>{{m[0][0], m[0][2]}, {m[2][0], m[2][2]}}),
           -determinant(Mat<T, 2, 2>{{m[0][0], m[0][1]}, {m[2][0], m[2][1]}})},
          {determinant(Mat<T, 2, 2>{{m[0][1], m[0][2]}, {m[1][1], m[1][2]}}),
           -determinant(Mat<T, 2, 2>{{m[0][0], m[0][2]}, {m[1][0], m[1][2]}}),
           determinant(Mat<T, 2, 2>{{m[0][0], m[0][1]}, {m[1][0], m[1][1]}})}};
}

template <typename T, int N>
constexpr Mat<T, N, N> adjoint(math::Mat<T, N, N> const &m) noexcept {
  return transpose(cofactors(m));
}

template <typename T, int N>
constexpr Mat<T, N, N> inverse(math::Mat<T, N, N> const &m) noexcept {
  return adjoint(m) / determinant(m);
}

template <typename T>
constexpr Mat<T, 3, 4> rigid_inverse(math::Mat<T, 3, 4> const &m) noexcept {
  auto const translation = math::Vec3f{m[0][3], m[1][3], m[2][3]};
  auto const retval_upper_left = math::Mat3x3f{{m[0][0], m[1][0], m[2][0]},
                                               {m[0][1], m[1][1], m[2][1]},
                                               {m[0][2], m[1][2], m[2][2]}};
  return {{retval_upper_left[0][0],
           retval_upper_left[0][1],
           retval_upper_left[0][2],
           -(retval_upper_left[0] * translation)},
          {retval_upper_left[1][0],
           retval_upper_left[1][1],
           retval_upper_left[1][2],
           -(retval_upper_left[1] * translation)},
          {retval_upper_left[2][0],
           retval_upper_left[2][1],
           retval_upper_left[2][2],
           -(retval_upper_left[2] * translation)}};
}

template <typename T>
constexpr Mat<T, 4, 4> rigid_inverse(math::Mat<T, 4, 4> const &m) noexcept {
  auto const translation = math::Vec3f{m[0][3], m[1][3], m[2][3]};
  auto const retval_upper_left = math::Mat3x3f{{m[0][0], m[1][0], m[2][0]},
                                               {m[0][1], m[1][1], m[2][1]},
                                               {m[0][2], m[1][2], m[2][2]}};
  return {{retval_upper_left[0][0],
           retval_upper_left[0][1],
           retval_upper_left[0][2],
           -(retval_upper_left[0] * translation)},
          {retval_upper_left[1][0],
           retval_upper_left[1][1],
           retval_upper_left[1][2],
           -(retval_upper_left[1] * translation)},
          {retval_upper_left[2][0],
           retval_upper_left[2][1],
           retval_upper_left[2][2],
           -(retval_upper_left[2] * translation)},
          {T(0), T(0), T(0), T(1)}};
}

template <typename T>
constexpr Mat<T, 3, 4> affine_inverse(math::Mat<T, 3, 4> const &m) noexcept {
  auto const translation = math::Vec3f{m[0][3], m[1][3], m[2][3]};
  auto const retval_upper_left =
      inverse(math::Mat3x3f{{m[0][0], m[0][1], m[0][2]},
                            {m[1][0], m[1][1], m[1][2]},
                            {m[2][0], m[2][1], m[2][2]}});
  return {{retval_upper_left[0][0],
           retval_upper_left[0][1],
           retval_upper_left[0][2],
           -(retval_upper_left[0] * translation)},
          {retval_upper_left[1][0],
           retval_upper_left[1][1],
           retval_upper_left[1][2],
           -(retval_upper_left[1] * translation)},
          {retval_upper_left[2][0],
           retval_upper_left[2][1],
           retval_upper_left[2][2],
           -(retval_upper_left[2] * translation)}};
}

template <typename T>
constexpr Mat<T, 4, 4> affine_inverse(math::Mat<T, 4, 4> const &m) noexcept {
  auto const translation = math::Vec3f{m[0][3], m[1][3], m[2][3]};
  auto const retval_upper_left =
      inverse(math::Mat3x3f{{m[0][0], m[0][1], m[0][2]},
                            {m[1][0], m[1][1], m[1][2]},
                            {m[2][0], m[2][1], m[2][2]}});
  return {{retval_upper_left[0][0],
           retval_upper_left[0][1],
           retval_upper_left[0][2],
           -(retval_upper_left[0] * translation)},
          {retval_upper_left[1][0],
           retval_upper_left[1][1],
           retval_upper_left[1][2],
           -(retval_upper_left[1] * translation)},
          {retval_upper_left[2][0],
           retval_upper_left[2][1],
           retval_upper_left[2][2],
           -(retval_upper_left[2] * translation)},
          {T(0), T(0), T(0), T(1)}};
}
} // namespace marlon::math

#endif
