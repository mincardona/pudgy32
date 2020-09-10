cmake_minimum_required(VERSION 3.10)

project(pudgy32-cmake VERSION 0.1.0)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# library
add_subdirectory(pudgy32)
# executable
add_subdirectory(p32test)
