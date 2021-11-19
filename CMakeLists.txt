cmake_minimum_required(VERSION 3.1)

project(test_projector)

set(ARCH 1)  # 0: aarch64, 1: x86

SET(CMAKE_BUILD_TYPE "Debug")
add_compile_options(-O0 -g3 -ggdb3)

include_directories(include)

add_executable(test_eigen test_eigen.cpp)
add_executable(test_quad test_quad.cpp Geometry.cpp Quadrilateral.cpp)
add_executable(test_find_max_rect test_find_max_rect.cpp find_max_rect.cpp)

target_link_libraries(test_quad pthread)
