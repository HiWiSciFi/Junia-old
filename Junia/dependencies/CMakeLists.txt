add_subdirectory("glfw")

	target_include_directories(Junia
		PRIVATE
			"${CMAKE_CURRENT_SOURCE_DIR}/glfw/include"
	)
