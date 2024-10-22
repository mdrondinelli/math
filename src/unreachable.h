#ifndef MARLON_MATH_UNREACHABLE_H
#define MARLON_MATH_UNREACHABLE_H

namespace marlon {
namespace math {
[[noreturn]] inline void unreachable() {
#if defined(__GNUC__)
  __builtin_unreachable();
#elif defined(_MSC_VER)
  __assume(false);
#endif
}
} // namespace math
} // namespace marlon

#endif