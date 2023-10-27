#pragma once

#include <vulkan/vulkan.hpp>

namespace Junia::Vulkan {

class Buffer {
public:
	Buffer(VkDeviceSize size, VkBufferUsageFlags usage);
	~Buffer();

	void SetData(void* data);

private:
	VkDeviceSize size;
	VkBuffer buffer;
	VkDeviceMemory memory;
};

} // namespace Junia::Vulkan
