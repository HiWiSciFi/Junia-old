add_executable(Editor)

	set_property(TARGET Editor PROPERTY CXX_STANDARD 17)

	set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

	target_sources(Editor
		PRIVATE
			"${SRC_DIR}/Editor.cpp"
			"${SRC_DIR}/Editor.hpp"
	)

	target_link_libraries(Editor
		PUBLIC
			Junia
	)
