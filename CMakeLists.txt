cmake_minimum_required(VERSION 3.15)
project(Lab1)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(or-tools)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O4 -DNDEBUG")

add_executable(main main.cpp scorer.h data.h)
add_executable(optimize optimization.cpp scorer.h data.h)
target_link_libraries(optimize ortools::ortools)
