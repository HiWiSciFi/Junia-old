#pragma once

#include <vulkan/vulkan.hpp>

#include "CommandBuffer.hpp"

namespace Vulkan {

// -----------------------------------------------------------------------------
// -------------------------------- Declaration --------------------------------
// -----------------------------------------------------------------------------

class Instance;

extern Instance* g_instance;

class Instance final {
public:
	Instance();
	~Instance();

private:
	VkInstance instance;

	VkPhysicalDevice physicalDevice;
	VkPhysicalDeviceMemoryProperties physicalDeviceMemoryProperties;

	VkDevice device;

	VkCommandPool transferCommandPool;
	CommandBuffer transferCommandBuffer;

	extern VkPhysicalDeviceMemoryProperties g_physicalDeviceMemoryProperties;
	extern VkCommandPool g_transferCommandPool;
	extern CommandBuffer g_transferCommandBuffer;
	extern VkQueue g_transferQueue;
};

} // namespace Vulkan
