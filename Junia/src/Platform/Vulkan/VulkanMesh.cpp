#include "VulkanMesh.hpp"
#include "VulkanDevice.hpp"

namespace Vulkan {

extern VulkanDevice* vkDevice;

VulkanMesh::VulkanMesh(const std::string& path, FileType type) {
	LoadModel(path, type);

	/*VkVertexInputBindingDescription bindingDescription{ };
	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(JMath::Vec3f);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
	VkVertexInputAttributeDescription attributeDescription{ };
	attributeDescription.binding = 0;
	attributeDescription.location = 0;
	attributeDescription.format = VK_FORMAT_R32G32B32_SFLOAT;
	attributeDescription.offset = 0;*/

	{
		VkDeviceSize vertexBufferSize = sizeof(JMath::Vec3f) * vertices.size();
		VulkanBuffer stagingBuffer(vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		stagingBuffer.FillData(vertices.data());
		vertexBuffer = new VulkanBuffer(vertexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		vertexBuffer->FillData(stagingBuffer);
	}

	{
		VkDeviceSize indexBufferSize = sizeof(JMath::Vec3ui) * indices.size();
		VulkanBuffer stagingBuffer(indexBufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
		stagingBuffer.FillData(indices.data());
		indexBuffer = new VulkanBuffer(indexBufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
		indexBuffer->FillData(stagingBuffer);
	}
}

VulkanMesh::~VulkanMesh() {
	delete vertexBuffer;
	delete indexBuffer;
}

void VulkanMesh::BindVertexBuffer(VkCommandBuffer commandBuffer) {
	VkDeviceSize offsets[] = { 0 };
	VkBuffer buffer = vertexBuffer->Get();
	vkCmdBindVertexBuffers(commandBuffer, 0, 1, &buffer, offsets);
}

void VulkanMesh::BindIndexBuffer(VkCommandBuffer commandBuffer) {
	vkCmdBindIndexBuffer(commandBuffer, indexBuffer->Get(), 0, VK_INDEX_TYPE_UINT32);
}

} // namespace Vulkan
