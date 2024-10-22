cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(Sandbox C CXX)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if (MSVC)
  add_compile_options(/W4 /WX)
else()
  add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()
add_subdirectory(lib/Catch2-3.6.0)
add_executable(
  tests
  src/mat.cpp
  src/quat.cpp
  src/vec.cpp
)
target_link_libraries(tests Catch2::Catch2WithMain)
