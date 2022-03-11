cmake_minimum_required(VERSION 3.20)
project(Sorting C)

set(CMAKE_C_STANDARD 11)

add_executable(Sorting main.c)

add_subdirectory(libs)
target_link_libraries(Sorting algorithms)
target_link_libraries(Sorting data_structures)