cmake_minimum_required(VERSION 3.8)
project(lattice)

set(CMAKE_CXX_STANDARD 11)
include_directories(/usr/local/include/eigen3/)
set(SOURCE_FILES lattice.cpp main.cpp)
add_executable(lattice ${SOURCE_FILES})