add_executable(Editor)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(OUTPUT_DIR "${PROJECT_BINARY_DIR}/Editor")

set_target_properties(Editor
	PROPERTIES
		CXX_STANDARD 17
		RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/Debug"
		RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/Release"
		FOLDER "Junia"
)

target_sources(Editor
	PRIVATE
		"${SRC_DIR}/Editor.cpp"
		"${SRC_DIR}/Scenes/Scene1.hpp"
		"${SRC_DIR}/Scenes/Scene1.cpp"
		"${SRC_DIR}/Systems/GravitySystem.hpp"
		"${SRC_DIR}/Systems/GravitySystem.cpp"
		"${SRC_DIR}/Shaders/shader1.vert"
		"${SRC_DIR}/Shaders/shader1.frag"
)

target_link_libraries(Editor
	PUBLIC
		Junia
)

add_custom_command(TARGET Editor PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory
		"${OUTPUT_DIR}/$<CONFIG>/Shaders"
)

add_custom_command(TARGET Editor POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${SRC_DIR}/Shaders/shader1_vert.spv"
		"${SRC_DIR}/Shaders/shader1_frag.spv"
		"${OUTPUT_DIR}/$<CONFIG>/Shaders"
)

add_custom_command(TARGET Editor POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${SRC_DIR}/Assets"
		"${OUTPUT_DIR}/$<CONFIG>/Assets"
)
