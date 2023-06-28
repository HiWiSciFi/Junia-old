#include "VulkanRenderPackage.hpp"

namespace Vulkan {

extern VulkanRenderPass* renderPass;

VulkanRenderPackage::VulkanRenderPackage(std::shared_ptr<Junia::Mesh> mesh, std::shared_ptr<Junia::Material> material)
	: pipeline(renderPass->Get(), material) {
}

VulkanRenderPackage::~VulkanRenderPackage() {
}

} // namespace Vulkan
