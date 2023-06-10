#pragma once

#include <vulkan/vulkan.hpp>

namespace Vulkan {

class VulkanCommandBuffer {
public:
	VulkanCommandBuffer(VkCommandPool pool);
	~VulkanCommandBuffer();

private:
	VkCommandPool pool = nullptr;
	VkCommandBuffer buffer = nullptr;
};

} // namespace Vulkan
