cmake_minimum_required(VERSION 3.2)

project(Junia)

	set(DEPENDENCY_DIR "${CMAKE_SOURCE_DIR}/dependencies")
	include("${DEPENDENCY_DIR}/dependencies.cmake")

	add_subdirectory("Junia")
	add_subdirectory("Editor")
