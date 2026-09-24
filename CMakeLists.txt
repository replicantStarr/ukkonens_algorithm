cmake_minimum_version(VERSION 4.3.0)

project(suffix_tree_implementation VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(tests tests/tests.cpp)

add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(src PUBLIC headers)
target_link_libraries(tests PRIVATE headers)

