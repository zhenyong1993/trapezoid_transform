cmake_minimum_required(VERSION 3.1)

project(test_projector)

SET(CMAKE_BUILD_TYPE "Debug")
add_compile_options(-O0 -g3 -ggdb3)

include_directories(include)

add_executable(test_quad test_quad.cpp Geometry.cpp Quadrilateral.cpp)
add_library(max_inner_rect SHARED MaxInnerRect.cpp Geometry.cpp Quadrilateral.cpp)

if(NOT ${CMAKE_SYSTEM_NAME} MATCHES "Android")  # if(DEFINED ANDROID_ABI)
target_link_libraries(test_quad pthread)
target_link_libraries(max_inner_rect pthread)
endif()
