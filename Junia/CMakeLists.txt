add_library(Junia STATIC)

set_target_properties(Junia
	PROPERTIES
		CXX_STANDARD_REQUIRED ON
		CXX_STANDARD 20
		FOLDER "Junia"
)

set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

## ---------------------------------------------------------------------------------------------------------------------
## ---------------------------------------------------- Dependencies ---------------------------------------------------
## ---------------------------------------------------------------------------------------------------------------------

set(JUNIA_DEPENDENCY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies")

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
add_subdirectory("${JUNIA_DEPENDENCY_DIR}/glfw")
set(GLFW_LIBRARY "glfw")
set_property(TARGET glfw PROPERTY FOLDER "Junia/Dependencies/GLFW")
if (TARGET update_mappings)
	set_property(TARGET update_mappings PROPERTY FOLDER "Junia/Dependencies/GLFW")
endif()

# Vulkan
find_package(Vulkan)
if(NOT ${Vulkan_FOUND})
	message(FATAL_ERROR "Vulkan could not be found! Make sure $VULKAN_SDK environment variable is set if the problem persists.")
endif()

# SPIRV-Reflect
set(SPIRV_REFLECT_EXECUTABLE OFF CACHE BOOL "" FORCE)
set(SPIRV_REFLECT_STATIC_LIB ON CACHE BOOL "" FORCE)
set(SPIRV_REFLECT_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SPIRV_REFLECT_ENABLE_ASSERTS OFF CACHE BOOL "" FORCE)
set(SPIRV_REFLECT_ASAN OFF CACHE BOOL "" FORCE)
add_subdirectory("${JUNIA_DEPENDENCY_DIR}/SPIRV-Reflect")
set(SPIRV_REFLECT_LIBRARY "spirv-reflect-static")

# VMA
add_subdirectory("dependencies/VulkanMemoryAllocator")

## ---------------------------------------------------------------------------------------------------------------------
## ------------------------------------------------------- Files -------------------------------------------------------
## ---------------------------------------------------------------------------------------------------------------------

target_include_directories(Junia
	PUBLIC
		"${INCLUDE_DIR}"
		"${Vulkan_INCLUDE_DIR}"
)

target_sources(Junia
	PRIVATE
		"${SRC_DIR}/Junia.cpp"

		"${SRC_DIR}/Junia/Core/Version.cpp"
		"${SRC_DIR}/Junia/Core/Logger.cpp"
		"${SRC_DIR}/Junia/Core/Log.cpp"
		"${SRC_DIR}/Junia/Core/Window.cpp"
		"${SRC_DIR}/Junia/Core/Input.cpp"
		"${SRC_DIR}/Junia/Core/Keycodes.cpp"
		"${SRC_DIR}/Junia/Core/InternalLoggers.cpp"
		"${SRC_DIR}/Junia/Core/Monitor.cpp"
		"${SRC_DIR}/Junia/Core/Scene.cpp"

		"${SRC_DIR}/Platform/OS/Windows/WindowsFileSystem.cpp"
		"${SRC_DIR}/Platform/OS/Linux/LinuxFileSystem.cpp"
		"${SRC_DIR}/Platform/OS/Windows/WindowsTime.cpp"
		"${SRC_DIR}/Platform/OS/Linux/LinuxTime.cpp"
		"${SRC_DIR}/Platform/OS/Windows/WindowsMessageBox.cpp"
		"${SRC_DIR}/Platform/OS/Linux/LinuxMessageBox.cpp"

		"${SRC_DIR}/Junia/ECS/ECS.cpp"
		"${SRC_DIR}/Junia/ECS/Systems/RendererSystem.cpp"

		"${SRC_DIR}/Junia/Events/Events.cpp"
		"${SRC_DIR}/Junia/Events/InputEvents.cpp"
		"${SRC_DIR}/Junia/Events/WindowEvents.cpp"

		"${SRC_DIR}/Junia/Renderer/Material.cpp"
		"${SRC_DIR}/Junia/Renderer/Mesh.cpp"
		"${SRC_DIR}/Junia/Renderer/RenderDevice.cpp"
		"${SRC_DIR}/Junia/Renderer/Renderer.cpp"
		"${SRC_DIR}/Junia/Renderer/Shader.cpp"
		"${SRC_DIR}/Junia/Renderer/Surface.cpp"

		"${SRC_DIR}/Platform/GLFW.cpp"
		"${SRC_DIR}/Platform/GLFW/GlfwInput.cpp"
		"${SRC_DIR}/Platform/GLFW/GlfwMonitor.cpp"
		"${SRC_DIR}/Platform/GLFW/GlfwWindow.cpp"

		"${SRC_DIR}/Platform/Vulkan/Buffer.cpp"
		"${SRC_DIR}/Platform/Vulkan/CommandBuffer.cpp"
		"${SRC_DIR}/Platform/Vulkan/CommandPool.cpp"
		"${SRC_DIR}/Platform/Vulkan/DescriptorSet.cpp"
		"${SRC_DIR}/Platform/Vulkan/ExtensionLoader.cpp"
		"${SRC_DIR}/Platform/Vulkan/Image.cpp"
		"${SRC_DIR}/Platform/Vulkan/Instance.cpp"
		"${SRC_DIR}/Platform/Vulkan/Pipeline.cpp"
		"${SRC_DIR}/Platform/Vulkan/Queue.cpp"
		"${SRC_DIR}/Platform/Vulkan/RenderDevice.cpp"
		"${SRC_DIR}/Platform/Vulkan/RenderPass.cpp"
		"${SRC_DIR}/Platform/Vulkan/Swapchain.cpp"
)

## ---------------------------------------------------------------------------------------------------------------------
## ------------------------------------------------------ Linking ------------------------------------------------------
## ---------------------------------------------------------------------------------------------------------------------

target_link_libraries(Junia
	PRIVATE
		"${GLFW_LIBRARY}"
		"${Vulkan_LIBRARY}"
		"${SPIRV_REFLECT_LIBRARY}"
		GPUOpen::VulkanMemoryAllocator
)

if (UNIX)
	target_link_libraries(Junia
		PRIVATE
			"X11"
	)
endif (UNIX)
