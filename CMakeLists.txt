cmake_minimum_required(VERSION 3.20)

project(Junia VERSION 1.0.0 LANGUAGES CXX)

option(JUNIA_BUILD_EDITOR "Build the Junia Editor" ON)

if (JUNIA_BUILD_EDITOR)
	message(STATUS "Including Junia Editor")
endif()

add_subdirectory("Junia")

if (JUNIA_BUILD_EDITOR)
	add_subdirectory("Editor")
endif()
