add_executable(Editor)

	set_property(TARGET Editor PROPERTY CXX_STANDARD 17)

	set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

	target_sources(Editor
		PRIVATE
			"${SRC_DIR}/Editor.cpp"
			"${SRC_DIR}/Shaders/shader1.vert"
			"${SRC_DIR}/Shaders/shader1.frag"
	)

	add_custom_command(TARGET Editor POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
				"${SRC_DIR}/Shaders/shader1_vert.spv"
				"${CMAKE_CURRENT_BINARY_DIR}/Shaders/shader1_vert.spv"
	)

	add_custom_command(TARGET Editor POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy
				"${SRC_DIR}/Shaders/shader1_frag.spv"
				"${CMAKE_CURRENT_BINARY_DIR}/Shaders/shader1_frag.spv"
	)

	target_link_libraries(Editor
		PUBLIC
			Junia
	)
