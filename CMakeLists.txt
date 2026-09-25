cmake_minimum_required(VERSION 4.3.0)
project(suffix_tree_implementation VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(Ukkonen tests/test_runner.cpp)

target_sources(Ukkonen 
	PRIVATE src/suffix_tree.cpp
	PUBLIC src/headers/suffix_tree.hpp)

target_sources(Ukkonen
	PRIVATE tests/test_runner.cpp
	PRIVATE tests/headers/json.hpp
)

target_include_directories(Ukkonen PUBLIC src/headers)
target_include_directories(Ukkonen PRIVATE tests/headers)
