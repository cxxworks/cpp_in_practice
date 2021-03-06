project(samples)

cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-std=c++14")

add_subdirectory(common)
add_subdirectory(basic)