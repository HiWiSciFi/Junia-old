#include <Junia/Renderer/Material.hpp>

#include "../../Platform/Vulkan/VulkanMaterial.hpp"

namespace Junia {

std::shared_ptr<Material> Material::Create(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader) {
	return std::make_shared<Vulkan::VulkanMaterial>(vertexShader, fragmentShader);
}

Material::~Material() {
}

} // namespace Junia
