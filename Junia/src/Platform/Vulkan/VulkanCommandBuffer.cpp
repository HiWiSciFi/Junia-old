#include "VulkanCommandBuffer.hpp"
#include "VulkanDevice.hpp"

namespace Vulkan {

extern VulkanDevice* vkDevice;

VulkanCommandBuffer::VulkanCommandBuffer(VkCommandPool pool) : pool(pool) {
	VkCommandBufferAllocateInfo bufferAllocInfo{ };
	bufferAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	bufferAllocInfo.commandBufferCount = 1;
	bufferAllocInfo.commandPool = pool;
	bufferAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;

	if (vkAllocateCommandBuffers(vkDevice->GetLogical(), &bufferAllocInfo, &buffer) != VK_SUCCESS)
		throw std::runtime_error("failed to allocate command buffer");
}

VulkanCommandBuffer::~VulkanCommandBuffer() {
	vkFreeCommandBuffers(vkDevice->GetLogical(), pool, 1, &buffer);
}

void VulkanCommandBuffer::BeginRecord() {
	VkCommandBufferBeginInfo beginInfo{ };
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	if (vkBeginCommandBuffer(buffer, &beginInfo) != VK_SUCCESS)
		throw std::runtime_error("failed to begin recording command buffer");
}

void VulkanCommandBuffer::EndRecord() {
	if (vkEndCommandBuffer(buffer) != VK_SUCCESS)
		throw std::runtime_error("failed to record command buffer");
}

}
