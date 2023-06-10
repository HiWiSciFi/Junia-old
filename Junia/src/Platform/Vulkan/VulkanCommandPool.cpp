#include "VulkanCommandPool.hpp"
#include "VulkanDevice.hpp"
#include <stdexcept>

namespace Vulkan {

extern VulkanDevice* vkDevice;

VulkanCommandPool::VulkanCommandPool(uint8_t maxInFlightFrames) {
	VkCommandPoolCreateInfo poolInfo{ };
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = vkDevice->GetGraphicsQueueIndex();

	if (vkCreateCommandPool(vkDevice->GetLogical(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
		throw std::runtime_error("failed to create command pool");

	commandBuffers.resize(maxInFlightFrames);

	VkCommandBufferAllocateInfo allocInfo{ };
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

	if (vkAllocateCommandBuffers(vkDevice->GetLogical(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
		throw std::runtime_error("failed to create command buffer");
}

VulkanCommandPool::~VulkanCommandPool() {
	vkDestroyCommandPool(vkDevice->GetLogical(), commandPool, nullptr);
}

void VulkanCommandPool::BeginRecordCommandBuffer(uint32_t currentFrame) {
	VkCommandBufferBeginInfo beginInfo{ };
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

	if (vkBeginCommandBuffer(commandBuffers[currentFrame], &beginInfo) != VK_SUCCESS)
		throw std::runtime_error("failed to begin recording command buffer");
}

void VulkanCommandPool::EndRecordCommandBuffer(uint32_t currentFrame) {
	if (vkEndCommandBuffer(commandBuffers[currentFrame]) != VK_SUCCESS)
		throw std::runtime_error("failed to record command buffer");
}

} // namespace Vulkan
