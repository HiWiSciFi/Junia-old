#include "VulkanCommandPool.hpp"
#include "VulkanDevice.hpp"
#include <stdexcept>

namespace Vulkan {

extern VulkanDevice* vkDevice;

VulkanCommandPool::VulkanCommandPool(uint32_t queueIndex, uint32_t bufferCount) {
	VkCommandPoolCreateInfo poolInfo{ };
	poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolInfo.queueFamilyIndex = queueIndex;
	if (vkCreateCommandPool(vkDevice->GetLogical(), &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
		throw std::runtime_error("failed to create command pool");

	CreateBuffers(bufferCount);
}

VulkanCommandPool::~VulkanCommandPool() {
	vkDestroyCommandPool(vkDevice->GetLogical(), commandPool, nullptr);
}

VkCommandPool VulkanCommandPool::GetPool() const {
	return commandPool;
}

uint32_t VulkanCommandPool::CreateBuffers(uint32_t count) {
	VkCommandBufferAllocateInfo allocInfo{ };
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.commandPool = commandPool;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandBufferCount = count;

	uint32_t index = static_cast<uint32_t>(commandBuffers.size());
	commandBuffers.resize(static_cast<size_t>(index + count));
	if (vkAllocateCommandBuffers(vkDevice->GetLogical(), &allocInfo, &commandBuffers[index]) != VK_SUCCESS)
		throw std::runtime_error("failed to allocate command buffer");
	return index;
}

void VulkanCommandPool::DeleteBuffers(uint32_t index, uint32_t count) {
	vkFreeCommandBuffers(vkDevice->GetLogical(), commandPool, count, &commandBuffers[index]);
	commandBuffers.erase(commandBuffers.begin() + index, commandBuffers.begin() + index + count);
}

uint32_t VulkanCommandPool::GetBufferCount() const {
	return commandBuffers.size();
}

void VulkanCommandPool::BeginRecordBuffer(uint32_t index) const {
	VkCommandBufferBeginInfo beginInfo{ };
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	if (vkBeginCommandBuffer(commandBuffers[index], &beginInfo) != VK_SUCCESS)
		throw std::runtime_error("failed to begin recording command buffer");
}

void VulkanCommandPool::EndRecordBuffer(uint32_t index) const {
	if (vkEndCommandBuffer(commandBuffers[index]) != VK_SUCCESS)
		throw std::runtime_error("failed to record command buffer");
}

void VulkanCommandPool::ResetBuffer(uint32_t index) const {
	vkResetCommandBuffer(commandBuffers[index], 0);
}

void VulkanCommandPool::SubmitBuffer(uint32_t index, VkQueue queue, VkSemaphore* waitSemaphores, uint32_t waitSemaphoreCount, VkPipelineStageFlags* waitStages,
	VkSemaphore* signalSemaphores, uint32_t signalSemaphoreCount, VkFence fence) const {
	VkSubmitInfo submitInfo{ };
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffers[index];
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.pWaitSemaphores = waitSemaphores;
	submitInfo.waitSemaphoreCount = waitSemaphoreCount;
	submitInfo.pSignalSemaphores = signalSemaphores;
	submitInfo.signalSemaphoreCount = signalSemaphoreCount;
	if (vkQueueSubmit(queue, 1, &submitInfo, fence) != VK_SUCCESS)
		throw std::runtime_error("failed to submit command buffer");
}

void VulkanCommandPool::CmdCopyBuffer(uint32_t index, const VulkanBuffer& src, uint32_t srcOffset, const VulkanBuffer& dst, uint32_t dstOffset, uint64_t size) const {
	VkBufferCopy copyRegion{ };
	copyRegion.srcOffset = srcOffset;
	copyRegion.dstOffset = dstOffset;
	copyRegion.size = size;
	vkCmdCopyBuffer(commandBuffers[index], src.GetBuffer(), dst.GetBuffer(), 1, &copyRegion);
}

void VulkanCommandPool::CmdDraw(uint32_t index, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) const {
	vkCmdDraw(commandBuffers[index], vertexCount, instanceCount, firstVertex, firstInstance);
}

} // namespace Vulkan
