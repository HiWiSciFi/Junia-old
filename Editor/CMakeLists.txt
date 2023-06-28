add_executable(Editor)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(OUTPUT_DIR "${PROJECT_BINARY_DIR}/Editor")

set_target_properties(Editor
	PROPERTIES
		CXX_STANDARD_REQUIRED ON
		CXX_STANDARD 20
		RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/Debug"
		RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/Release"
		FOLDER "Junia"
)

target_sources(Editor
	PRIVATE
		"${SRC_DIR}/Editor.cpp"
		"${SRC_DIR}/Scenes/Scene1.cpp"
		"${SRC_DIR}/Systems/GravitySystem.cpp"
)

target_link_libraries(Editor
	PUBLIC
		Junia
)

add_custom_command(TARGET Editor POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
		"${SRC_DIR}/Assets"
		"${OUTPUT_DIR}/$<CONFIG>/Assets"
)
