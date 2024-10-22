#ifndef MARLON_MATH_AABB_BOUNDS_H
#define MARLON_MATH_AABB_BOUNDS_H

#include "vec.h"

namespace marlon::math {
template <typename T, int N> struct Aabb {
  Vec<T, N> min;
  Vec<T, N> max;

  Aabb() noexcept = default;

  constexpr Aabb(Vec<T, N> const &p) noexcept
      : Aabb{p, p} {}

  constexpr Aabb(Vec<T, N> const &min, Vec<T, N> const &max) noexcept
      : min{min}, max{max} {}

  constexpr Aabb<T, 2> xy() const noexcept {
    return Aabb<T, 2>{min.xy(), max.xy()};
  }

  constexpr Aabb<T, 3> xyz() const noexcept {
    return Aabb<T, 3>{min.xyz(), max.xyz()};
  }
};

using Aabb2i = Aabb<std::int32_t, 2>;
using Aabb3i = Aabb<std::int32_t, 3>;
using Aabb2f = Aabb<float, 2>;
using Aabb3f = Aabb<float, 3>;
using Aabb2d = Aabb<double, 2>;
using Aabb3d = Aabb<double, 3>;

template <typename T, int N>
inline Vec<T, N> center(Aabb<T, N> const &box) noexcept {
  return (box.min + box.max) / T(2);
}

template <typename T, int N>
inline Vec<T, N> extents(Aabb<T, N> const &box) noexcept {
  return box.max - box.min;
}

template <typename T> inline T area(Aabb<T, 2> const &box) noexcept {
  auto const d = extents(box);
  return d.x * d.y;
}

template <typename T> inline T volume(Aabb<T, 3> const &box) noexcept {
  auto const d = extents(box);
  return d.x * d.y * d.z;
}

template <typename T, int N>
inline Aabb<T, N> expand(Aabb<T, N> const &box,
                         Vec<T, N> const &amount) noexcept {
  return {box.min - amount, box.max + amount};
}

template <typename T, int N>
inline Aabb<T, N> expand(Aabb<T, N> const &box, T amount) noexcept {
  return expand(box, Vec<T, N>::all(amount));
}

template <typename T, int N>
inline Aabb<T, N> merge(Aabb<T, N> const &first,
                        Aabb<T, N> const &second) noexcept {
  return {min(first.min, second.min), max(first.max, second.max)};
}

template <typename T, int N>
inline Aabb<T, N> merge(Aabb<T, N> const &box,
                        Vec<T, N> const &point) noexcept {
  return {min(box.min, point), max(box.max, point)};
}

template <typename T, int N>
inline Aabb<T, N> merge(Vec<T, N> const &point,
                        Aabb<T, N> const &box) noexcept {
  return merge(box, point);
}

template <typename T, int N>
inline bool overlaps(Aabb<T, N> const &first,
                     Aabb<T, N> const &second) noexcept {
  for (auto i = 0; i != N; ++i) {
    if (first.min[i] >= second.max[i] || second.min[i] >= first.max[i]) {
      return false;
    }
  }
  return true;
}
} // namespace marlon::math

#endif