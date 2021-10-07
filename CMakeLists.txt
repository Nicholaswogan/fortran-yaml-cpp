cmake_minimum_required(VERSION 3.4)
project(test CXX)
add_subdirectory(yaml-cpp)
enable_language(Fortran)

set(CMAKE_CXX_STANDARD 11)

add_library(fortran-yaml-cpp wrapper.f90 wrapper.cpp)
target_link_libraries(fortran-yaml-cpp yaml-cpp)

add_executable(main main.f90)
target_link_libraries(main fortran-yaml-cpp)




