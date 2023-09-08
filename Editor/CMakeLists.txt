add_executable(Editor)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(RES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/res")
set(OUTPUT_DIR "${PROJECT_BINARY_DIR}/Editor")

set_target_properties(Editor
	PROPERTIES
		CXX_STANDARD_REQUIRED ON
		CXX_STANDARD 20
		RUNTIME_OUTPUT_DIRECTORY_DEBUG "${OUTPUT_DIR}/Debug"
		RUNTIME_OUTPUT_DIRECTORY_RELEASE "${OUTPUT_DIR}/Release"
		RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}"
		FOLDER "Junia"
)

target_sources(Editor PRIVATE
	"${SRC_DIR}/Editor.cpp"
	"${SRC_DIR}/Scenes/Scene1.cpp"
	"${SRC_DIR}/Systems/GravitySystem.cpp"
)

target_link_libraries(Editor PUBLIC
	Junia
)

set(RESOURCE_FILES
	"${RES_DIR}/Models/Square.obj"
	"${RES_DIR}/Models/Triangle.obj"

	"${RES_DIR}/Shaders/shader1.vert"
	"${RES_DIR}/Shaders/shader1.frag"
	"${RES_DIR}/Shaders/shader2.vert"
	"${RES_DIR}/Shaders/shader2.frag"
)

add_custom_target(EditorResources
	${CMAKE_COMMAND} -E remove_directory
		"${OUTPUT_DIR}/$<CONFIG>/res"
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${RES_DIR}"
		"${OUTPUT_DIR}/$<CONFIG>/res"
	COMMENT "Copying resource files for Junia Editor" VERBATIM
	SOURCES
		"${RESOURCE_FILES}"
)

add_dependencies(Editor EditorResources)
