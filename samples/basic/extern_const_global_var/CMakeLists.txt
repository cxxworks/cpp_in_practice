project(extern_const_global_var)

cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS "-std=c++11")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} CPP_SOURCES)

add_executable(test_extern_const_global_var ${CPP_SOURCES})