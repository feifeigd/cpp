cmake_minimum_required(VERSION 3.0)

project(cpp)

if(UNIX)
	add_definitions(-std=c++11)
endif()
include_directories(include)
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(r-value_reference)
