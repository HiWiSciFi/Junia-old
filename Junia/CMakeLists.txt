add_library(Junia STATIC)

	set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
	set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

	target_compile_definitions(Junia
		PRIVATE
			JELOG_MAX_TRACE
	)

	target_sources(Junia
		PRIVATE
			"${SRC_DIR}/Junia.cpp"
			"${SRC_DIR}/Junia/Core/Core.hpp"
			"${SRC_DIR}/Junia/Core/Window.cpp"
			"${SRC_DIR}/Junia/Core/Logger.cpp"
			"${SRC_DIR}/Junia/Core/Log.cpp"

			"${INCLUDE_DIR}/Junia.hpp"
			"${INCLUDE_DIR}/Junia/Core/Window.hpp"
			"${INCLUDE_DIR}/Junia/Core/Logger.hpp"
			"${INCLUDE_DIR}/Junia/Core/Log.hpp"
	)

	target_include_directories(Junia
		PUBLIC
			"${INCLUDE_DIR}"
	)

	target_link_libraries(Junia
		PRIVATE
			"${GLFW_LIB}"
			"${GLAD_LIB}"
	)
