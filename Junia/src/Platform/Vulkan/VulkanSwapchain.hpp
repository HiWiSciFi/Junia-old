#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>
#include <cstdint>
#include "VulkanRenderPass.hpp"
#include "VulkanGraphicsPipeline.hpp"
#include "VulkanCommandPool.hpp"

namespace Vulkan
{
	class VulkanSwapchain
	{
	private:
		std::vector<VkImage> images{ };
		std::vector<VkImageView> imageViews{ };
		std::vector<VkFramebuffer> framebuffers{ };
		VkSwapchainKHR swapchain = nullptr;
		VkFormat format;
		VkExtent2D extent;
		VulkanRenderPass* renderPass = nullptr;
		VulkanGraphicsPipeline* graphicsPipeline = nullptr;
		VulkanCommandPool* commandPool = nullptr;

		std::vector<VkSemaphore> imageAvailableSemaphores{ };
		std::vector<VkSemaphore> renderFinishedSemaphores{ };
		std::vector<VkFence> inFlightFences{ };
		uint8_t maxInFlight;

		uint32_t currentFrame = 0;

	public:
		VulkanSwapchain(GLFWwindow* window, VkSurfaceKHR surface, uint8_t maxInFlightFrames);
		~VulkanSwapchain();

		void Draw();
	};
}
