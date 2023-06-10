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
}

VulkanCommandBuffer::~VulkanCommandBuffer() {
	vkFreeCommandBuffers(vkDevice->GetLogical(), pool, 1, &buffer);
}

}
