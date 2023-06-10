#pragma once

#include <vulkan/vulkan.hpp>
#include <cstdint>

namespace Vulkan {

class VulkanBuffer {
public:
	VulkanBuffer(size_t size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties);
	~VulkanBuffer();

	size_t GetSize() const;
	virtual void SetData(void* data);
	VkBuffer GetBuffer();

protected:
	size_t size;
	VkBuffer buffer = nullptr;
	VkDeviceMemory bufferMemory = nullptr;
};

} // namespace Vulkan
