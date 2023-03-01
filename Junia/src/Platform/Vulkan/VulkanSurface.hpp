#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <Junia/Renderer/Surface.hpp>
#include <Junia/Core/Window.hpp>
#include "VulkanSwapchain.hpp"

namespace Vulkan
{
	class VulkanSurface : public Junia::Surface
	{
	private:
		VkSurfaceKHR surface = nullptr;
		VulkanSwapchain* swapchain = nullptr;

	public:
		VulkanSurface(GLFWwindow* window);
		~VulkanSurface() override;
	};
}
