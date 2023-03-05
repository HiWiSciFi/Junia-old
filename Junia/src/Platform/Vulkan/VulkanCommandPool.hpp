#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <cstdint>

namespace Vulkan
{
	class VulkanCommandPool
	{
	private:
		VkCommandPool commandPool = nullptr;
		VkCommandBuffer commandBuffer = nullptr;

	public:
		VulkanCommandPool();
		~VulkanCommandPool();

		inline VkCommandBuffer GetBuffer() const { return commandBuffer; }
		void BeginRecordCommandBuffer();
		void EndRecordCommandBuffer();
	};
}
