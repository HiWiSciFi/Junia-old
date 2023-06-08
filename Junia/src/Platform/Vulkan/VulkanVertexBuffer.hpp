#pragma once

#include <vulkan/vulkan.hpp>
#include <cstdint>
#include "VulkanBuffer.hpp"

namespace Vulkan {

class VulkanVertexBuffer : public VulkanBuffer {
public:
	VulkanVertexBuffer(size_t size, void* data);
	~VulkanVertexBuffer();

	virtual void SetData(void* data) override;

private:
	VulkanBuffer stagingBuffer;
};

} // namespace Vulkan
