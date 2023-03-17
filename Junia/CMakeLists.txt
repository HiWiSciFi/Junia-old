add_library(Junia STATIC)

	set_property(TARGET Junia PROPERTY CXX_STANDARD 17)

	set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
	set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

	target_compile_definitions(Junia
		PRIVATE
			JELOG_MAX_TRACE
	)

	target_sources(Junia
		PRIVATE
			"${INCLUDE_DIR}/Junia.hpp"
			"${SRC_DIR}/Junia.cpp"

			"${INCLUDE_DIR}/Junia/Core/Version.hpp"
			"${SRC_DIR}/Junia/Core/Version.cpp"
			"${INCLUDE_DIR}/Junia/Core/Logger.hpp"
			"${SRC_DIR}/Junia/Core/Logger.cpp"
			"${INCLUDE_DIR}/Junia/Core/Log.hpp"
			"${SRC_DIR}/Junia/Core/Log.cpp"
			"${INCLUDE_DIR}/Junia/Core/Window.hpp"
			"${SRC_DIR}/Junia/Core/Window.cpp"
			"${INCLUDE_DIR}/Junia/Core/Input.hpp"
			"${SRC_DIR}/Junia/Core/Input.cpp"
			"${INCLUDE_DIR}/Junia/Core/Keycodes.hpp"
			"${SRC_DIR}/Junia/Core/Keycodes.cpp"
			"${INCLUDE_DIR}/Junia/Core/IdPool.hpp"
			"${SRC_DIR}/Junia/Core/InternalLoggers.hpp"
			"${SRC_DIR}/Junia/Core/InternalLoggers.cpp"
			"${INCLUDE_DIR}/Junia/Core/Monitor.hpp"
			"${SRC_DIR}/Junia/Core/Monitor.cpp"
			"${INCLUDE_DIR}/Junia/Core/Scene.hpp"
			"${SRC_DIR}/Junia/Core/Scene.cpp"

			"${INCLUDE_DIR}/Junia/Core/FileSystem.hpp"
			"${SRC_DIR}/Platform/OS/Windows/WindowsFileSystem.cpp"
			"${SRC_DIR}/Platform/OS/Linux/LinuxFileSystem.cpp"
			"${INCLUDE_DIR}/Junia/Core/Time.hpp"
			"${SRC_DIR}/Platform/OS/Windows/WindowsTime.cpp"
			"${SRC_DIR}/Platform/OS/Linux/LinuxTime.cpp"

			"${INCLUDE_DIR}/Junia/ECS/ECS.hpp"
			"${SRC_DIR}/Junia/ECS/ECS.cpp"

			"${INCLUDE_DIR}/Junia/Events/Events.hpp"
			"${SRC_DIR}/Junia/Events/Events.cpp"
			"${INCLUDE_DIR}/Junia/Events/InputEvents.hpp"
			"${SRC_DIR}/Junia/Events/InputEvents.cpp"

			"${INCLUDE_DIR}/Junia/ECS/Components.hpp"
			"${INCLUDE_DIR}/Junia/ECS/ComponentContainer.hpp"
			"${INCLUDE_DIR}/Junia/ECS/Components/Transform.hpp"
			"${INCLUDE_DIR}/Junia/ECS/Components/EntityInfo.hpp"

			"${INCLUDE_DIR}/JMath.hpp"
			"${INCLUDE_DIR}/JMath/Types.hpp"
			"${INCLUDE_DIR}/JMath/Constants.hpp"
			"${INCLUDE_DIR}/JMath/Vectors.hpp"
			"${INCLUDE_DIR}/JMath/Vector1.hpp"
			"${INCLUDE_DIR}/JMath/Vector2.hpp"
			"${INCLUDE_DIR}/JMath/Vector3.hpp"
			"${INCLUDE_DIR}/JMath/Vector4.hpp"
			"${INCLUDE_DIR}/JMath/Matrices.hpp"
			"${INCLUDE_DIR}/JMath/Matrix2x2.hpp"
			"${INCLUDE_DIR}/JMath/Matrix2x3.hpp"
			"${INCLUDE_DIR}/JMath/Matrix2x4.hpp"
			"${INCLUDE_DIR}/JMath/Matrix3x2.hpp"
			"${INCLUDE_DIR}/JMath/Matrix3x3.hpp"
			"${INCLUDE_DIR}/JMath/Matrix3x4.hpp"
			"${INCLUDE_DIR}/JMath/Matrix4x2.hpp"
			"${INCLUDE_DIR}/JMath/Matrix4x3.hpp"
			"${INCLUDE_DIR}/JMath/Matrix4x4.hpp"
			"${INCLUDE_DIR}/JMath/Quaternion.hpp"
			"${INCLUDE_DIR}/JMath/Mathf.hpp"

			"${INCLUDE_DIR}/Junia/Renderer/Surface.hpp"
			"${SRC_DIR}/Junia/Renderer/Surface.cpp"
			"${INCLUDE_DIR}/Junia/Renderer/RenderDevice.hpp"
			"${SRC_DIR}/Junia/Renderer/RenderDevice.cpp"

			"${SRC_DIR}/Platform/GLFW.hpp"
			"${SRC_DIR}/Platform/GLFW.cpp"
			"${SRC_DIR}/Platform/GLFW/GlfwWindow.hpp"
			"${SRC_DIR}/Platform/GLFW/GlfwWindow.cpp"
			"${SRC_DIR}/Platform/GLFW/GlfwInput.hpp"
			"${SRC_DIR}/Platform/GLFW/GlfwInput.cpp"
			"${SRC_DIR}/Platform/GLFW/GlfwMonitor.hpp"
			"${SRC_DIR}/Platform/GLFW/GlfwMonitor.cpp"

			"${INCLUDE_DIR}/Platform/Vulkan.hpp"
			"${SRC_DIR}/Platform/Vulkan.cpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanExtensionLoader.hpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanExtensionLoader.cpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanDevice.hpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanDevice.cpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanSurface.hpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanSurface.cpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanSwapchain.hpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanSwapchain.cpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanRenderPass.hpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanRenderPass.cpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanGraphicsPipeline.hpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanGraphicsPipeline.cpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanCommandPool.hpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanCommandPool.cpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanCommandBuffer.hpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanCommandBuffer.cpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanVertexBuffer.hpp"
			"${SRC_DIR}/Platform/Vulkan/VulkanVertexBuffer.cpp"

			"${INCLUDE_DIR}/Platform/OpenAL.hpp"
			"${SRC_DIR}/Platform/OpenAL.cpp"
			"${INCLUDE_DIR}/Platform/OpenAL/Exception.hpp"
			"${INCLUDE_DIR}/Platform/OpenAL/OutputDevice.hpp"
			"${SRC_DIR}/Platform/OpenAL/OutputDevice.cpp"
	)

	target_include_directories(Junia
		PUBLIC
			"${INCLUDE_DIR}"
		PRIVATE
			"${Vulkan_INCLUDE_DIR}"
			"${OPENAL_INCLUDE_DIR}"
	)

	target_link_libraries(Junia
		PRIVATE
			"${GLFW_LIB}"
			"${Vulkan_LIBRARY}"
			"${OPENAL_LIBRARY}"
	)

	if (UNIX)
		target_link_libraries(Junia
		PRIVATE
			"X11"
			"Xrandr"
	)
	endif (UNIX)
