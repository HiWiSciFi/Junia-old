#include "VulkanBuffer.hpp"

#include <Junia/Log.hpp>
#include <vulkan/vulkan.hpp>

namespace Junia
{
	///////// VERTEX BUFFER /////////

	VulkanVertexBuffer::VulkanVertexBuffer(float* vertices, uint32_t size)
	{
		VkBufferCreateInfo bufferInfo{ };
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(device, &bufferInfo, nullptr, &vkBuf) != VK_SUCCESS)
			JELOG_BASE_CRIT("Vulkan: Failed to create vertex buffer!");

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(device, vkBuf, &memRequirements);
	}

	VulkanVertexBuffer::~VulkanVertexBuffer()
	{
		vkDestroyBuffer(device, vkBuf, nullptr);
	}

	void VulkanVertexBuffer::Bind() const
	{
	}

	void VulkanVertexBuffer::Unbind() const
	{
	}

	///////// INDEX BUFFER /////////

	VulkanIndexBuffer::VulkanIndexBuffer(uint32_t* indices, uint32_t count) : count(count)
	{

	}

	VulkanIndexBuffer::~VulkanIndexBuffer()
	{
	}

	void VulkanIndexBuffer::Bind() const
	{
	}

	void VulkanIndexBuffer::Unbind() const
	{
	}
}
