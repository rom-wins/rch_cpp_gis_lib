cmake_minimum_required(VERSION 3.9)

project(rch_cpp_gis_lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS Off)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(pybind11 CONFIG REQUIRED)
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_subdirectory(src)