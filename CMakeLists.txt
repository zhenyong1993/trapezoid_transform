cmake_minimum_required(VERSION 3.1)

project(test_projector)

set(ARCH 1)  # 0: aarch64, 1: x86

SET(CMAKE_BUILD_TYPE "Debug")
add_compile_options(-O0 -g3 -ggdb3)

include_directories(include)

add_executable(test_eigen test_eigen.cpp)
add_executable(test_line test_line.cpp Geometry.cpp Quadrilateral.cpp)
