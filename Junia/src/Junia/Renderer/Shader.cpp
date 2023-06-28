#include <Junia/Renderer/Shader.hpp>
#include <Junia/Core/FileSystem.hpp>
#include "../../Platform/Vulkan/VulkanShader.hpp"

#include <vector>

namespace Junia {

Shader::Shader(Type type) : type(type) { }

std::shared_ptr<Shader> Shader::Create(const std::string& path, Type type) {
	std::vector<uint8_t> shaderCode = ReadFileBinary(path);
	return std::make_shared<Vulkan::VulkanShader>(shaderCode, type);
}

Shader::~Shader() { }

} // namespace Junia
