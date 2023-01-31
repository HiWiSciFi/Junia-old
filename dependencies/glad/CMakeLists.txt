project(glad)

	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	add_library(glad STATIC)
		target_sources(glad
			PRIVATE
				"${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c"
		)

		target_include_directories(glad
			PUBLIC
				"${CMAKE_CURRENT_SOURCE_DIR}/include"
		)
