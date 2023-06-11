#pragma once

#include <vulkan/vulkan.hpp>

namespace Vulkan {

class VulkanCommandBuffer {
public:
	VulkanCommandBuffer(VkCommandPool pool);
	~VulkanCommandBuffer();

	void BeginRecord();
	void EndRecord();

private:
	VkCommandPool pool = nullptr;
	VkCommandBuffer buffer = nullptr;
};

} // namespace Vulkan
