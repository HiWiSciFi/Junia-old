#include "VulkanBuffer.hpp"
#include "VulkanDevice.hpp"

namespace Vulkan {

extern VulkanDevice* vkDevice;

static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
	VkPhysicalDeviceMemoryProperties memoryProperties;
	vkGetPhysicalDeviceMemoryProperties(vkDevice->GetPhysical(), &memoryProperties);
	for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
		if (typeFilter & (1 << i) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}
	throw std::runtime_error("failed to find suitable memory type");
}

VulkanBuffer::VulkanBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties) : bufferSize(size) {
	VkBufferCreateInfo bufferCreateInfo{ };
	bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferCreateInfo.size = size;
	bufferCreateInfo.usage = usage;
	bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

	if (vkCreateBuffer(vkDevice->GetLogical(), &bufferCreateInfo, nullptr, &buffer) != VK_SUCCESS)
		throw std::runtime_error("failed to create vertex buffer");

	VkMemoryRequirements memoryRequirements;
	vkGetBufferMemoryRequirements(vkDevice->GetLogical(), buffer, &memoryRequirements);

	VkMemoryAllocateInfo allocInfo{ };
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memoryRequirements.size;
	allocInfo.memoryTypeIndex = FindMemoryType(memoryRequirements.memoryTypeBits, properties);
	if (vkAllocateMemory(vkDevice->GetLogical(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
		throw std::runtime_error("failed to allocate vertex buffer memory");

	vkBindBufferMemory(vkDevice->GetLogical(), buffer, bufferMemory, 0);
}

VulkanBuffer::~VulkanBuffer() {
	vkDeviceWaitIdle(vkDevice->GetLogical());
	vkDestroyBuffer(vkDevice->GetLogical(), buffer, nullptr);
	vkFreeMemory(vkDevice->GetLogical(), bufferMemory, nullptr);
}

void VulkanBuffer::FillData(void* data) {
	void* bufferData;
	vkMapMemory(vkDevice->GetLogical(), bufferMemory, 0, bufferSize, 0, &bufferData);
	memcpy(bufferData, data, static_cast<size_t>(bufferSize));
	vkUnmapMemory(vkDevice->GetLogical(), bufferMemory);
}

void VulkanBuffer::FillData(VulkanBuffer& other) {
	if (bufferSize != other.bufferSize)
		throw std::runtime_error("source and target buffer sizes don't match");

	// TODO: make command pool and transfer queue available from vkDevice
	VkCommandPool transferCommandPool;
	VkCommandPoolCreateInfo poolCreateInfo{ };
	poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolCreateInfo.queueFamilyIndex = vkDevice->GetTransferQueueIndex();
	if (vkCreateCommandPool(vkDevice->GetLogical(), &poolCreateInfo, nullptr, &transferCommandPool) != VK_SUCCESS)
		throw std::runtime_error("failed to create transfer command pool");

	VkCommandBufferAllocateInfo allocInfo{ };
	allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	allocInfo.commandPool = transferCommandPool;
	allocInfo.commandBufferCount = 1;

	VkCommandBuffer commandBuffer;
	if (vkAllocateCommandBuffers(vkDevice->GetLogical(), &allocInfo, &commandBuffer) != VK_SUCCESS)
		throw std::runtime_error("failed to allocate transfer command buffer");

	VkCommandBufferBeginInfo beginInfo{ };
	beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	VkBufferCopy copyRegion{ };
	copyRegion.srcOffset = 0;
	copyRegion.dstOffset = 0;
	copyRegion.size = bufferSize;
	vkCmdCopyBuffer(commandBuffer, other.buffer, buffer, 1, &copyRegion);

	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo{ };
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;

	// TODO: use transfer queue
	vkQueueSubmit(vkDevice->GetTransferQueue(), 1, &submitInfo, VK_NULL_HANDLE);
	vkDevice->TransferQueueWaitIdle();

	vkFreeCommandBuffers(vkDevice->GetLogical(), transferCommandPool, 1, &commandBuffer);
	vkDestroyCommandPool(vkDevice->GetLogical(), transferCommandPool, nullptr);
}

} // namespace Vulkan
