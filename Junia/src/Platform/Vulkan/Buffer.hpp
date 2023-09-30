#pragma once

#include <vulkan/vulkan.hpp>

namespace Vulkan {

// -----------------------------------------------------------------------------
// -------------------------------- Declaration --------------------------------
// -----------------------------------------------------------------------------

class Buffer final {
public:
	Buffer();
	Buffer(VkDeviceSize size, VkBufferUsageFlags usage);
	~Buffer();

	void SetData(void* data);

private:
	VkBuffer buffer;
	VkDeviceMemory memory;
	VkDeviceSize size;
};

} // namespace Vulkan
