#include "Buffer.hpp"

#include <stdexcept>

#include "GlobalState.hpp"

namespace Vulkan {

Buffer::Buffer() : buffer(VK_NULL_HANDLE), memory(VK_NULL_HANDLE), size(0) {
}

Buffer::Buffer(VkDeviceSize size, VkBufferUsageFlags usage)
	: size(size) {
	// Buffer has to be Transfer Destination
	usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;

	// Create Buffer
	VkBufferCreateInfo bufferCreateInfo{ };
	bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferCreateInfo.size = this->size;
	bufferCreateInfo.usage = usage;
	bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	if (vkCreateBuffer(g_device, &bufferCreateInfo, VK_NULL_HANDLE, &this->buffer) != VK_SUCCESS)
		throw std::runtime_error("failed to create buffer");

	// Get Buffer memory requirements
	VkMemoryRequirements memoryRequirements;
	vkGetBufferMemoryRequirements(g_device, this->buffer, &memoryRequirements);

	// Find buffer memory type
	VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
	uint32_t memoryTypeIndex = g_physicalDeviceMemoryProperties.memoryTypeCount;
	for (uint32_t i = 0; i < g_physicalDeviceMemoryProperties.memoryTypeCount; i++) {
		if (memoryRequirements.memoryTypeBits & (1 << i) && (g_physicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			memoryTypeIndex = i;
			break;
		}
	}
	if (memoryTypeIndex == g_physicalDeviceMemoryProperties.memoryTypeCount)
		throw std::runtime_error("failed to find suitable memory type");

	// Allocate buffer memory
	VkMemoryAllocateInfo allocInfo{ };
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memoryRequirements.size;
	allocInfo.memoryTypeIndex = memoryTypeIndex;
	if (vkAllocateMemory(g_device, &allocInfo, VK_NULL_HANDLE, &this->memory) != VK_SUCCESS)
		throw std::runtime_error("failed to allocate buffer memory");

	// Bind Buffer to allocated memory
	vkBindBufferMemory(g_device, this->buffer, this->memory, 0);
}

Buffer::~Buffer() {
	vkDestroyBuffer(g_device, this->buffer, VK_NULL_HANDLE);
	vkFreeMemory(g_device, this->memory, VK_NULL_HANDLE);
}

void Buffer::SetData(void* data) {

	// Buffer for transferring Data to GPU
	VkBuffer transferBuffer;
	VkDeviceMemory transferMemory;

	// Create transferBuffer
	VkBufferCreateInfo bufferCreateInfo{ };
	bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferCreateInfo.size = this->size;
	bufferCreateInfo.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	if (vkCreateBuffer(g_device, &bufferCreateInfo, VK_NULL_HANDLE, &transferBuffer) != VK_SUCCESS)
		throw std::runtime_error("failed to create buffer");

	// Get transferBuffer Memory Requirements
	VkMemoryRequirements memoryRequirements;
	vkGetBufferMemoryRequirements(g_device, transferBuffer, &memoryRequirements);

	// Find Memory Type
	VkMemoryPropertyFlags properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
	uint32_t memoryTypeIndex = g_physicalDeviceMemoryProperties.memoryTypeCount;
	for (uint32_t i = 0; i < g_physicalDeviceMemoryProperties.memoryTypeCount; i++) {
		if (memoryRequirements.memoryTypeBits & (1 << i) && (g_physicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			memoryTypeIndex = i;
			break;
		}
	}
	if (memoryTypeIndex == g_physicalDeviceMemoryProperties.memoryTypeCount)
		throw std::runtime_error("failed to find suitable memory type");

	// Allocate transferBuffer Memory
	VkMemoryAllocateInfo allocInfo{ };
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memoryRequirements.size;
	allocInfo.memoryTypeIndex = memoryTypeIndex;
	if (vkAllocateMemory(g_device, &allocInfo, VK_NULL_HANDLE, &transferMemory) != VK_SUCCESS)
		throw std::runtime_error("failed to allocate buffer memory");

	// Bind transferBuffer to transferMemory
	vkBindBufferMemory(g_device, transferBuffer, transferMemory, 0);

	// Transfer data to GPU
	void* bufferData;
	vkMapMemory(g_device, transferMemory, 0, this->size, 0, &bufferData);
	memcpy(bufferData, data, static_cast<size_t>(this->size));
	vkUnmapMemory(g_device, transferMemory);

	// Execute CopyBuffer Command
	g_transferCommandBuffer.Begin();
	g_transferCommandBuffer.CmdCopyBuffer(transferBuffer, 0, this->buffer, 0, this->size);
	g_transferCommandBuffer.End();
	g_transferCommandBuffer.Submit();

	// Wait for transfer to be finished
	vkQueueWaitIdle(g_transferQueue);

	// Free transfer buffer
	vkDestroyBuffer(g_device, transferBuffer, VK_NULL_HANDLE);
	vkFreeMemory(g_device, transferMemory, VK_NULL_HANDLE);
}

} // namespace Vulkan
