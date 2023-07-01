#pragma once

#include <Junia/Renderer/Mesh.hpp>
#include <vulkan/vulkan.hpp>
#include "VulkanBuffer.hpp"

namespace Vulkan {

class VulkanMesh : public Junia::Mesh {
private:
	VulkanBuffer* vertexBuffer = nullptr;
	VulkanBuffer* indexBuffer = nullptr;

public:
	VulkanMesh(const std::string& path, FileType type);
	~VulkanMesh() override;

	void BindVertexBuffer(VkCommandBuffer commandBuffer);
	void BindIndexBuffer(VkCommandBuffer commandBuffer);
};

} // namespace Vulkan
