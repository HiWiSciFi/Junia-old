#pragma once

#include <vulkan/vulkan.h>

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
	};
}
