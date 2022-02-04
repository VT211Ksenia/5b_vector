cmake_minimum_required(VERSION 3.20)
project(untitled10 C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled10 main.c libs/algorithms/array/array.c libs/algorithms/array/array.h libs/algorithms/algorithm.c libs/algorithms/algorithm.h libs/data_structures/vector/vector.c libs/data_structures/vector/vector.h)

add_subdirectory(libs)
target_link_libraries(untitled10 data_structures)
target_link_libraries(untitled10 algorithms)