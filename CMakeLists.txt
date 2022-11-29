cmake_minimum_required(VERSION 3.23)

project(Tutorial)
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED true)
	file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp")
	add_executable(Tutorial ${SOURCES})
