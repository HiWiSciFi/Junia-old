#pragma once

#include <vulkan/vulkan.hpp>
#include <cstdint>
#include <vector>
#include "VulkanBuffer.hpp"

namespace Vulkan {

// write a class wrapping a vulkan command pool
// it should have a vector of command buffers
// it should have a function to create a command buffer
// it should have a function to delete a command buffer
// it should have a function to begin recording a command buffer
// it should have a function to end recording a command buffer
// it should have a function to get a command buffer
// it should have a function to get the command pool
// it should have a function to get the command buffer count

class VulkanCommandPool {
private:
	VkCommandPool commandPool = nullptr;
	std::vector<VkCommandBuffer> commandBuffers{ };

public:
	VulkanCommandPool(uint32_t queueIndex, uint32_t bufferCount);
	~VulkanCommandPool();

	VkCommandPool GetPool() const;

	uint32_t CreateBuffers(uint32_t count = 1);
	void DeleteBuffers(uint32_t index, uint32_t count = 1);
	uint32_t GetBufferCount() const;

	// TODO: remove
	VkCommandBuffer GetBuffer(uint32_t index) const {
		return commandBuffers[index];
	}

	void BeginRecordBuffer(uint32_t index) const;
	void EndRecordBuffer(uint32_t index) const;
	void ResetBuffer(uint32_t index) const;
	void SubmitBuffer(uint32_t index, VkQueue queue,
		VkSemaphore* waitSemaphores = nullptr, uint32_t waitSemaphoreCount = 0,
		VkPipelineStageFlags* waitStages = nullptr,
		VkSemaphore* signalSemaphores = nullptr, uint32_t signalSemaphoreCount = 0,
		VkFence fence = nullptr) const;

	void CmdCopyBuffer(uint32_t index,
		const VulkanBuffer& src, uint32_t srcOffset,
		const VulkanBuffer& dst, uint32_t dstOffset,
		uint64_t size) const;
	void CmdDraw(uint32_t index,
		uint32_t vertexCount, uint32_t instanceCount,
		uint32_t firstVertex, uint32_t firstInstance) const;
};

} // namespace Vulkan
