add_library(Junia STATIC)

	target_sources(Junia
		PRIVATE
			"${CMAKE_CURRENT_SOURCE_DIR}/src/Junia.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/include/Junia.hpp"
	)

	target_include_directories(Junia
		PUBLIC
			"${CMAKE_CURRENT_SOURCE_DIR}/include"
	)

	add_subdirectory("dependencies")

	target_link_libraries(Junia
		PRIVATE
			glfw
	)
