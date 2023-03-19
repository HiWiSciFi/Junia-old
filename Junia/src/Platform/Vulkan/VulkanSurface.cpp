#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_VULKAN
#include "VulkanSurface.hpp"
#include <stdexcept>

namespace Vulkan
{
	extern VkInstance vkInstance;

	VulkanSurface::VulkanSurface(Junia::Window* window)
	{
		if (glfwCreateWindowSurface(vkInstance, reinterpret_cast<GLFWwindow*>(window->GetNative()), nullptr, &surface) != VK_SUCCESS)
			throw std::runtime_error("failed to create window surface");
		swapchain = new VulkanSwapchain(window, surface, 2);
	}

	VulkanSurface::~VulkanSurface()
	{
		delete swapchain;
		vkDestroySurfaceKHR(vkInstance, surface, nullptr);
	}

	void VulkanSurface::FramebufferResized()
	{
		swapchain->FramebufferResized();
	}

	void VulkanSurface::Draw()
	{
		swapchain->Draw();
	}
}
