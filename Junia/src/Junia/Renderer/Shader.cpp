#include <Junia/Renderer/Shader.hpp>

#include <vector>
#include <Junia/Core/FileSystem.hpp>

namespace Junia {

Shader::Shader(Type type) : type(type) { }

std::shared_ptr<Shader> Shader::Create(const std::string& path, Type type) {
	std::vector<std::uint8_t> shaderCode = ReadFileBinary(path);
	return nullptr;
}

Shader::~Shader() { }

} // namespace Junia
