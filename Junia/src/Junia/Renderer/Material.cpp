#include <Junia/Renderer/Material.hpp>

namespace Junia {

Material::Material(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader)
	: vertexShader(vertexShader), fragmentShader(fragmentShader) { }

std::shared_ptr<Material> Material::Create(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader) {
	return std::shared_ptr<Material>(new Material(vertexShader, fragmentShader));
}

Material::~Material() {
}

} // namespace Junia
