add_executable(Editor)

	target_sources(Editor
		PRIVATE
			"${CMAKE_CURRENT_SOURCE_DIR}/src/Editor.cpp"
			"${CMAKE_CURRENT_SOURCE_DIR}/src/Editor.hpp"
	)

	target_link_libraries(Editor
		PUBLIC
			Junia
	)
