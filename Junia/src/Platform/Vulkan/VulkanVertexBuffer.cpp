#include "VulkanVertexBuffer.hpp"
#include "VulkanDevice.hpp"
#include <stdexcept>

namespace Vulkan {

extern VulkanDevice* vkDevice;

VulkanVertexBuffer::VulkanVertexBuffer(size_t size, void* data)
	: VulkanBuffer(size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT),
	stagingBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) {
	if (data != nullptr) stagingBuffer.SetData(data);
}

VulkanVertexBuffer::~VulkanVertexBuffer() {
	vkDestroyBuffer(vkDevice->GetLogical(), buffer, nullptr);
	vkFreeMemory(vkDevice->GetLogical(), bufferMemory, nullptr);
}

void VulkanVertexBuffer::SetData(void* data) {
	stagingBuffer.SetData(data);

	VkCommandBufferAllocateInfo allocInfo{ };
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = commandPool;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(vkDevice->GetLogical(), &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo{ };
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	VkBufferCopy copyRegion{ };
	copyRegion.srcOffset = 0;
	copyRegion.dstOffset = 0;
	copyRegion.size = size;
	vkCmdCopyBuffer(commandBuffer, stagingBuffer.buffer, buffer, 1, &copyRegion);

	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo{ };
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	vkQueueSubmit(vkDevice->GetGraphicsQueue(), 1, &submitInfo, nullptr);
	vkQueueWaitIdle(vkDevice->GetGraphicsQueue());

	vkFreeCommandBuffers(vkDevice->GetLogical(), commandPool, 1, &commandBuffer);
}

} // namespace Vulkan
