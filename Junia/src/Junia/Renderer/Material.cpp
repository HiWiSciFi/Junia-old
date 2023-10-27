#include <Junia/Renderer/Material.hpp>

namespace Junia {

std::shared_ptr<Material> Material::Create(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader) {
	return nullptr;
}

Material::~Material() {
}

} // namespace Junia
