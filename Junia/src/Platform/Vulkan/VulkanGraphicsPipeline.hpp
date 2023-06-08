#pragma once

#include <vulkan/vulkan.hpp>
#include "VulkanRenderPass.hpp"

namespace Vulkan
{
	class VulkanGraphicsPipeline
	{
	private:
		VkPipeline graphicsPipeline = nullptr;
		VkPipelineLayout layout = nullptr;
		VkShaderModule vertexShader = nullptr;
		VkShaderModule fragmentShader = nullptr;
		VkViewport viewport{ };
		VkRect2D scissor{ };

	public:
		VulkanGraphicsPipeline(VkExtent2D extent, VulkanRenderPass* renderPass);
		~VulkanGraphicsPipeline();

		void Bind(VkCommandBuffer buffer);
	};
}
