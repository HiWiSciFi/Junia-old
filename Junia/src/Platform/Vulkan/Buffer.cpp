#include "Buffer.hpp"

#include <vk_mem_alloc.h>

#include "Instance.hpp"
#include "CommandBuffer.hpp"

namespace Junia::Vulkan {

//[[nodiscard]] static std::uint32_t GetMemoryTypeIndex(VkMemoryRequirements& memoryRequirements, VkMemoryPropertyFlags properties) {
//	std::uint32_t memoryTypeIndex = Vulkan::PhysicalDevice::GetMemoryProperties().memoryTypeCount;
//	for (std::uint32_t i = 0; i < Vulkan::PhysicalDevice::GetMemoryProperties().memoryTypeCount; i++) {
//		if (memoryRequirements.memoryTypeBits & (1 << i) && (Vulkan::PhysicalDevice::GetMemoryProperties().memoryTypes[i].propertyFlags & properties) == properties) {
//			memoryTypeIndex = i;
//			break;
//		}
//	}
//	if (memoryTypeIndex == Vulkan::PhysicalDevice::GetMemoryProperties().memoryTypeCount)
//		throw std::runtime_error("failed to find suitable memory type");
//	return memoryTypeIndex;
//}
//
//Vulkan::Buffer::Buffer(VkDeviceSize size, VkBufferUsageFlags usage) : size(size) {
//	// Set buffer as transfer destination
//	if (Vulkan::Device::TransferSupported()) usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
//
//	// Create buffer
//	VkBufferCreateInfo bufferCreateInfo = {
//		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
//		.size = size,
//		.usage = usage,
//		.sharingMode = VK_SHARING_MODE_EXCLUSIVE
//	};
//	if (vkCreateBuffer(Vulkan::Device::Get(), &bufferCreateInfo, VK_NULL_HANDLE, &this->buffer) != VK_SUCCESS)
//		throw std::runtime_error("Buffer could not be created");
//
//	// Get buffer memory requirements
//	VkMemoryRequirements memoryRequirements;
//	vkGetBufferMemoryRequirements(Vulkan::Device::Get(), this->buffer, &memoryRequirements);
//
//	// Find buffer memory type
//	VkMemoryPropertyFlags properties;
//	properties = Vulkan::Device::TransferSupported() ? (VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) : (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
//	std::uint32_t memoryTypeIndex = GetMemoryTypeIndex(memoryRequirements, properties);
//
//	// Allocate buffer memory
//	VkMemoryAllocateInfo allocInfo{
//		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
//		.allocationSize = memoryRequirements.size,
//		.memoryTypeIndex = memoryTypeIndex
//	};
//	if (vkAllocateMemory(Vulkan::Device::Get(), &allocInfo, VK_NULL_HANDLE, &this->memory) != VK_SUCCESS)
//		throw std::runtime_error("failed to allocate buffer memory");
//
//	// Bind Buffer to allocated memory
//	vkBindBufferMemory(Vulkan::Device::Get(), this->buffer, this->memory, 0);
//}
//
//Vulkan::Buffer::~Buffer() {
//	vkDestroyBuffer(Vulkan::Device::Get(), this->buffer, VK_NULL_HANDLE);
//	vkFreeMemory(Vulkan::Device::Get(), this->memory, VK_NULL_HANDLE);
//}
//
//void Vulkan::Buffer::SetData(void* data) {
//	if (!Vulkan::Device::TransferSupported()) {
//		void* bufferData;
//		vkMapMemory(Vulkan::Device::Get(), this->memory, 0, this->size, 0, &bufferData);
//		memcpy(bufferData, data, static_cast<std::size_t>(this->size));
//		vkUnmapMemory(Vulkan::Device::Get(), this->memory);
//		return;
//	}
//
//	VkBuffer transferBuffer;
//	VkDeviceMemory transferMemory;
//
//	// Create transfer buffer
//	VkBufferCreateInfo transferBufferCreateInfo = {
//		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
//		.size = this->size,
//		.usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
//		.sharingMode = VK_SHARING_MODE_EXCLUSIVE
//	};
//	if (vkCreateBuffer(Vulkan::Device::Get(), &transferBufferCreateInfo, VK_NULL_HANDLE, &transferBuffer) != VK_SUCCESS)
//		throw std::runtime_error("failed to create transfer buffer");
//
//	VkMemoryRequirements memoryRequirements;
//	vkGetBufferMemoryRequirements(Vulkan::Device::Get(), transferBuffer, &memoryRequirements);
//	VkMemoryPropertyFlags properties;
//	properties = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
//	std::uint32_t memoryTypeIndex = GetMemoryTypeIndex(memoryRequirements, properties);
//
//	VkMemoryAllocateInfo allocInfo = {
//		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
//		.allocationSize = memoryRequirements.size,
//		.memoryTypeIndex = memoryTypeIndex
//	};
//	if (vkAllocateMemory(Vulkan::Device::Get(), &allocInfo, VK_NULL_HANDLE, &transferMemory) != VK_SUCCESS)
//		throw std::runtime_error("failed to allocate transfer buffer");
//
//	vkBindBufferMemory(Vulkan::Device::Get(), transferBuffer, transferMemory, 0);
//
//	void* bufferData;
//	vkMapMemory(Vulkan::Device::Get(), transferMemory, 0, this->size, 0, &bufferData);
//	memcpy(bufferData, data, static_cast<std::size_t>(this->size));
//	vkUnmapMemory(Vulkan::Device::Get(), transferMemory);
//
//	Vulkan::CommandBuffer transferCommandBuffer; // TODO: exchange
//	transferCommandBuffer.Begin();
//	transferCommandBuffer.CmdCopyBuffer(transferBuffer, 0, this->buffer, 0, this->size);
//	transferCommandBuffer.End();
//	transferCommandBuffer.Submit();
//
//	vkQueueWaitIdle(Vulkan::Device::GetTransferQueue().Get());
//
//	vkDestroyBuffer(Vulkan::Device::Get(), transferBuffer, VK_NULL_HANDLE);
//	vkFreeMemory(Vulkan::Device::Get(), transferMemory, VK_NULL_HANDLE);
//}

} // namespace Junia::Vulkan
