#pragma once

#include <vulkan/vulkan.hpp>
#include <cstdint>
#include <vector>

namespace Vulkan {

class VulkanCommandPool {
private:
	VkCommandPool commandPool = nullptr;
	std::vector<VkCommandBuffer> commandBuffers{ };

public:
	VulkanCommandPool(uint8_t maxInFlightFrames);
	~VulkanCommandPool();

	inline VkCommandBuffer GetBuffer(uint8_t index) const { return commandBuffers[index]; }
	void BeginRecordCommandBuffer(uint32_t currentFrame);
	void EndRecordCommandBuffer(uint32_t currentFrame);
};

} // namespace Vulkan
