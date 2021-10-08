cmake_minimum_required(VERSION 3.4)
project(test CXX)
add_subdirectory(yaml-cpp)
enable_language(Fortran)

set(CMAKE_CXX_STANDARD 11)

add_library(fortran-yaml-cpp yaml_types.f90 yaml.f90 yaml.cpp)
target_link_libraries(fortran-yaml-cpp yaml-cpp)

add_executable(test test.f90)
target_link_libraries(test fortran-yaml-cpp)

add_executable(example example.f90)
target_link_libraries(example fortran-yaml-cpp)




