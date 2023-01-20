#include <Platform/Vulkan/LogicalDevice.hpp>

#include <vulkan/vulkan.h>

namespace Vulkan
{
	LogicalDevice::LogicalDevice()
	{

	}

	LogicalDevice::~LogicalDevice()
	{
		vkDestroyDevice(reinterpret_cast<VkDevice>(logicalDevice), nullptr);
	}
}
