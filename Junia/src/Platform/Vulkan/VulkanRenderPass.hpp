#pragma once

#include <vulkan/vulkan.hpp>
#include <JMath/Vector4.hpp>

namespace Vulkan
{
	class VulkanRenderPass
	{
	private:
		VkRenderPass renderPass = nullptr;
		VkClearValue clearValue{ };

	public:
		VulkanRenderPass() = default;
		VulkanRenderPass(JMath::Vec4f clearColor);
		~VulkanRenderPass();

		inline VkRenderPass Get() const { return renderPass; }

		void SetClearColor(JMath::Vec4f clearColor);

		void Begin(VkCommandBuffer commandBuffer, VkFramebuffer framebuffer, VkExtent2D extent) const;
		void End(VkCommandBuffer commandBuffer) const;
	};
}
