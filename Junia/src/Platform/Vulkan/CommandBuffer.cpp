#include "CommandBuffer.hpp"

#include <stdexcept>

#include "GlobalState.hpp"

namespace Vulkan {

CommandBuffer::CommandBuffer(VkCommandPool pool, VkQueue queue)
	: pool(pool), queue(queue) {
	VkCommandBufferAllocateInfo allocInfo{ };
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = pool;
	allocInfo.commandBufferCount = 1;
	if (vkAllocateCommandBuffers(g_device, &allocInfo, &this->buffer) != VK_SUCCESS)
		throw std::runtime_error("failed to allocate command buffer");
}

CommandBuffer::~CommandBuffer() {
	vkFreeCommandBuffers(g_device, this->pool, 1, &this->buffer);
}

void CommandBuffer::Begin() {
	VkCommandBufferBeginInfo beginInfo{ };
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	vkBeginCommandBuffer(this->buffer, &beginInfo);
}

void CommandBuffer::End() {
	vkEndCommandBuffer(this->buffer);
}

void CommandBuffer::Submit(VkFence fence) {
	VkSubmitInfo submitInfo{ };
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &this->buffer;
	vkQueueSubmit(this->queue, 1, &submitInfo, fence);
}

void CommandBuffer::CmdCopyBuffer(VkBuffer src, VkDeviceSize srcOffset, VkBuffer dst, VkDeviceSize dstOffset, VkDeviceSize size) {
	VkBufferCopy copyRegion{ };
	copyRegion.srcOffset = srcOffset;
	copyRegion.dstOffset = dstOffset;
	copyRegion.size = size;
	vkCmdCopyBuffer(this->buffer, src, dst, 1, &copyRegion);
}

} // namespace Vulkan
