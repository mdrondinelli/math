#ifndef MARLON_MATH_QUAT_H
#define MARLON_MATH_QUAT_H

#include <cassert>
#include <cmath>

#include <numbers>

#include "vec.h"

namespace marlon {
namespace math {
template <typename T> struct Quat {
  T w;
  Vec<T, 3> v;

  static auto zero() {
    return Quat<T>{T(0), Vec<T, 3>::zero()};
  }

  static auto identity() {
    return Quat<T>{T(1), Vec<T, 3>::zero()};
  }

  static auto axis_angle(Vec<T, 3> const &axis, T angle) {
    const auto half_angle = angle / T(2);
    return Quat{std::cos(half_angle), std::sin(half_angle) * axis};
  }

  Quat() noexcept = default;

  constexpr Quat(T w, Vec<T, 3> const &v) noexcept
      : w{w}, v{v} {}
};

using Quatf = Quat<float>;
using Quatd = Quat<double>;

template <typename T>
constexpr auto operator==(Quat<T> const &p, Quat<T> const &q) noexcept {
  return p.w == q.w && p.v == q.v;
}

template <typename T> constexpr auto operator+(Quat<T> const &q) noexcept {
  return q;
}

template <typename T> constexpr auto operator-(Quat<T> const &q) noexcept {
  return Quat<T>{-q.w, -q.v};
}

template <typename T> constexpr auto operator*(T s, Quat<T> const &q) noexcept {
  return Quat<T>{s * q.w, s * q.v};
}

template <typename T> constexpr auto operator*(Quat<T> const &q, T s) noexcept {
  return Quat<T>{q.w * s, q.v * s};
}

template <typename T> constexpr auto operator/(Quat<T> const &q, T s) noexcept {
  if constexpr (std::is_floating_point_v<T>) {
    return q * (1 / s);
  } else {
    return Quat<T>{q.w / s, q.v / s};
  }
}

template <typename T>
constexpr auto operator*(Quat<T> const &q1, Quat<T> const &q2) noexcept {
  return Quat<T>{q1.w * q2.w - dot(q1.v, q2.v),
                 q1.w * q2.v + q2.w * q1.v + cross(q1.v, q2.v)};
}

template <typename T>
constexpr auto operator+(Quat<T> const &q1, Quat<T> const &q2) noexcept {
  return Quat<T>{q1.w + q2.w, q1.v + q2.v};
}
template <typename T>
constexpr auto operator-(Quat<T> const &q1, Quat<T> const &q2) noexcept {
  return Quat<T>{q1.w - q2.w, q1.v - q2.v};
}

template <typename T>
constexpr auto &operator*=(Quat<T> &q1, Quat<T> const &q2) noexcept {
  return q1 = (q1 * q2);
}

template <typename T> constexpr auto &operator*=(Quat<T> &q, T s) noexcept {
  return q = q * s;
}

template <typename T> constexpr auto &operator/=(Quat<T> &q, T s) noexcept {
  return q = q / s;
}

template <typename T>
constexpr auto &operator+=(Quat<T> &q1, Quat<T> const &q2) noexcept {
  return q1 = (q1 + q2);
}

template <typename T>
constexpr auto &operator-=(Quat<T> &q1, Quat<T> const &q2) noexcept {
  return q1 = (q1 - q2);
}

template <typename T>
constexpr auto dot(Quat<T> const &q1, Quat<T> const &q2) noexcept {
  return q1.w * q2.w + dot(q1.v, q2.v);
}

template <typename T> constexpr auto length_squared(Quat<T> const &q) noexcept {
  return q.w * q.w + length_squared(q.v);
}

template <typename T> constexpr auto length(Quat<T> const &q) noexcept {
  return std::sqrt(length_squared(q));
}

template <typename T> constexpr auto normalize(Quat<T> const &q) noexcept {
  return q / length(q);
}

template <typename T> constexpr auto conjugate(Quat<T> const &q) noexcept {
  return Quat<T>{q.w, -q.v};
}

template <typename T> constexpr auto inverse(Quat<T> const &q) noexcept {
  return conjugate(q) / length_squared(q);
}

template <typename T> constexpr auto deg_to_rad(T deg) noexcept {
  return deg * (std::numbers::pi_v<T> / T(180));
}

template <typename T> constexpr auto rad_to_deg(T rad) noexcept {
  return rad * (T(180) / std::numbers::pi_v<T>);
}
} // namespace math
} // namespace marlon

#endif