#pragma once

#include <vulkan/vulkan.hpp>

namespace Vulkan {

class CommandPool {
public:
	CommandPool();
	~CommandPool();

private:
	VkCommandPool pool;
};

} // namespace Vulkan
