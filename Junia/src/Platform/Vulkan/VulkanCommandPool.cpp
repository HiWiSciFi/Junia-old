#include "VulkanCommandPool.hpp"
#include "VulkanDevice.hpp"
#include <stdexcept>

namespace Vulkan
{
	extern VulkanDevice* vkDevice;

	VulkanCommandPool::VulkanCommandPool()
	{
		VkCommandPoolCreateInfo poolInfo{ };
		poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
		poolInfo.queueFamilyIndex = vkDevice->GetGraphicsQueueIndex();

		if (vkCreateCommandPool(vkDevice->GetLogical(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
			throw std::runtime_error("failed to create command pool");

		VkCommandBufferAllocateInfo allocInfo{ };
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.commandPool = commandPool;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandBufferCount = 1;

		if (vkAllocateCommandBuffers(vkDevice->GetLogical(), &allocInfo, &commandBuffer) != VK_SUCCESS)
			throw std::runtime_error("failed to create command buffer");
	}

	VulkanCommandPool::~VulkanCommandPool()
	{
		vkDestroyCommandPool(vkDevice->GetLogical(), commandPool, nullptr);
	}

	void VulkanCommandPool::BeginRecordCommandBuffer()
	{
		VkCommandBufferBeginInfo beginInfo{ };
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

		if (vkBeginCommandBuffer(commandBuffer, &beginInfo) != VK_SUCCESS)
			throw std::runtime_error("failed to begin recording command buffer");
	}

	void VulkanCommandPool::EndRecordCommandBuffer()
	{
		if (vkEndCommandBuffer(commandBuffer) != VK_SUCCESS)
			throw std::runtime_error("failed to record command buffer");
	}
}
