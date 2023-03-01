#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include "VulkanRenderPass.hpp"
#include "VulkanGraphicsPipeline.hpp"

namespace Vulkan
{
	class VulkanSwapchain
	{
	private:
		std::vector<VkImage> images{ };
		std::vector<VkImageView> imageViews{ };
		VkSwapchainKHR swapchain = nullptr;
		VkFormat format;
		VkExtent2D extent;
		VulkanRenderPass* renderPass = nullptr;
		VulkanGraphicsPipeline* graphicsPipeline = nullptr;

	public:
		VulkanSwapchain(GLFWwindow* window, VkSurfaceKHR surface);
		~VulkanSwapchain();
	};
}
