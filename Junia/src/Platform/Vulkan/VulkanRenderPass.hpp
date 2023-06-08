#pragma once

#include <vulkan/vulkan.hpp>

namespace Vulkan
{
	class VulkanRenderPass
	{
	private:
		VkRenderPass renderPass = nullptr;

	public:
		VulkanRenderPass(VkFormat format);
		~VulkanRenderPass();

		inline VkRenderPass Get() const { return renderPass; }

		void Begin(VkFramebuffer framebuffer, VkExtent2D extent, VkCommandBuffer buffer);
		void End(VkCommandBuffer buffer);
	};
}
