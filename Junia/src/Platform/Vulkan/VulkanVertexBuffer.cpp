#include "VulkanVertexBuffer.hpp"
#include "VulkanDevice.hpp"
#include <stdexcept>
#include "VulkanCommandPool.hpp"

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

	static VulkanCommandPool vertexBufferAllocationPool(vkDevice->GetGraphicsQueueIndex(), 1);

	vertexBufferAllocationPool.BeginRecordBuffer(0);
	vertexBufferAllocationPool.CmdCopyBuffer(0, stagingBuffer, 0, *this, 0, size);
	vertexBufferAllocationPool.EndRecordBuffer(0);
	vertexBufferAllocationPool.SubmitBuffer(0, vkDevice->GetGraphicsQueue());
	vkQueueWaitIdle(vkDevice->GetGraphicsQueue());

	vertexBufferAllocationPool.ResetBuffer(0);
}

} // namespace Vulkan
