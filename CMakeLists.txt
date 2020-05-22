cmake_minimum_required(VERSION 3.14.6)

set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "-Wall")

message("Compiler: ${CMAKE_CXX_COMPILER}")
message("Flags: ${CMAKE_CXX_FLAGS}")

project(Project1)

add_subdirectory(data-structures)
add_subdirectory(graph-generator)
add_subdirectory(algorithms)

add_executable(Project1 main.cpp)
target_link_libraries(Project1 data-structures-lib algorithms-lib graph-generator-lib)