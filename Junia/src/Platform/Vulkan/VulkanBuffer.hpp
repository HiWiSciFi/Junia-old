#pragma once

#include <vulkan/vulkan.hpp>

namespace Vulkan {

class VulkanBuffer {
private:
	VkBuffer buffer;
	VkDeviceMemory bufferMemory;
	VkDeviceSize bufferSize;

public:
	VulkanBuffer() = default;
	VulkanBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
	~VulkanBuffer();

	inline VkDeviceSize GetSize() const { return bufferSize; }
	inline VkBuffer Get() const { return buffer; }

	void FillData(void* data);
	void FillData(VulkanBuffer& other);
};

} // namespace Vulkan
