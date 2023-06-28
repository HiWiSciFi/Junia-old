#pragma once

#include <vulkan/vulkan.hpp>
#include "VulkanRenderPass.hpp"
#include <Junia/Renderer/Material.hpp>

namespace Vulkan {

class VulkanGraphicsPipeline {
private:
	VkPipeline graphicsPipeline = nullptr;
	VkPipelineLayout layout = nullptr;
	std::shared_ptr<Junia::Material> material = nullptr;

public:
	VulkanGraphicsPipeline() = default;
	VulkanGraphicsPipeline(VkRenderPass renderPass, std::shared_ptr<Junia::Material> material);
	~VulkanGraphicsPipeline();

	void Bind(VkCommandBuffer buffer);
};

} // namespace Vulkan
