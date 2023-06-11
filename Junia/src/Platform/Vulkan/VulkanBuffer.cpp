#include "VulkanBuffer.hpp"
#include "VulkanDevice.hpp"
#include <stdexcept>

namespace Vulkan {

extern VulkanDevice* vkDevice;

static uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
	VkPhysicalDeviceMemoryProperties memoryProperties;
	vkGetPhysicalDeviceMemoryProperties(vkDevice->GetPhysical(), &memoryProperties);
	for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) {
		if (typeFilter & (1 << i)
			&& (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}
	throw std::runtime_error("failed to find suitable memory type");
}

VulkanBuffer::VulkanBuffer(size_t size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties) : size(size) {
	VkBufferCreateInfo bufferCreateInfo{ };
	bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufferCreateInfo.size = size;
	bufferCreateInfo.usage = usage;
	bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	if (vkCreateBuffer(vkDevice->GetLogical(), &bufferCreateInfo, nullptr, &buffer) != VK_SUCCESS)
		throw std::runtime_error("failed to create buffer");

	VkMemoryRequirements memoryRequirements;
	vkGetBufferMemoryRequirements(vkDevice->GetLogical(), buffer, &memoryRequirements);

	VkMemoryAllocateInfo allocInfo{ };
	allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	allocInfo.allocationSize = memoryRequirements.size;
	allocInfo.memoryTypeIndex = FindMemoryType(memoryRequirements.memoryTypeBits, properties);

	if (vkAllocateMemory(vkDevice->GetLogical(), &allocInfo, nullptr, &bufferMemory) != VK_SUCCESS)
		throw std::runtime_error("failed to allocate buffer memory");

	vkBindBufferMemory(vkDevice->GetLogical(), buffer, bufferMemory, 0);
}

VulkanBuffer::~VulkanBuffer() {
	vkDestroyBuffer(vkDevice->GetLogical(), buffer, nullptr);
	vkFreeMemory(vkDevice->GetLogical(), bufferMemory, nullptr);
}

size_t VulkanBuffer::GetSize() const {
	return size;
}

void VulkanBuffer::SetData(void* data) {
	void* dest;
	vkMapMemory(vkDevice->GetLogical(), bufferMemory, 0, size, 0, &dest);
	memcpy(dest, data, size);
	vkUnmapMemory(vkDevice->GetLogical(), bufferMemory);
}

VkBuffer VulkanBuffer::GetBuffer() const {
	return buffer;
}

} // namespace Vulkan
