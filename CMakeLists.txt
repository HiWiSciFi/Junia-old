cmake_minimum_required(VERSION 3.23)

project(Tutorial)
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED true)
	add_executable(Tutorial src/Main.cpp src/Calc.cpp)
