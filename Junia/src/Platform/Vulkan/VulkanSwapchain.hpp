#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>
#include <cstdint>
#include "VulkanRenderPass.hpp"
#include "VulkanGraphicsPipeline.hpp"
#include "VulkanCommandPool.hpp"
#include <Junia/Core/Window.hpp>

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

		VkSurfaceKHR surface = nullptr;
		Junia::Window* window = nullptr;

		bool resized = false;
		std::vector<VkSemaphore> imageAvailableSemaphores{ };
		std::vector<VkSemaphore> renderFinishedSemaphores{ };
		std::vector<VkFence> inFlightFences{ };
		uint8_t maxInFlight;

		uint32_t currentFrame = 0;

	public:
		VulkanSwapchain(Junia::Window* window, VkSurfaceKHR surface, uint8_t maxInFlightFrames);
		~VulkanSwapchain();

		void FramebufferResized();
		void Cleanup();
		void Recreate();
		void Draw();
	};
}
