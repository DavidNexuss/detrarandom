cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -ftree-vectorize -march=native -fopenmp")
set(CMAKE_COMPILE_WARNING_AS_ERROR OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(DOXYGEN_GENERATE_TREEVIEW YES)

project(detrarandom)

find_package(OpenMP)

file(GLOB_RECURSE SRC 
  detrarandom/*.cpp
)

add_executable(detrarandom_test ${SRC})
