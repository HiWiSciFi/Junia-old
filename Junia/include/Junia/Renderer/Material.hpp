#pragma once

#include "Shader.hpp"
#include <cstdint>
#include <vector>
#include <memory>

namespace Junia {

class Material {
private:
	std::shared_ptr<Shader> vertexShader;
	std::shared_ptr<Shader> fragmentShader;

	Material(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);

public:
	~Material();

	static std::shared_ptr<Material> Create(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);

	inline std::shared_ptr<Shader> GetVertexShader() const { return vertexShader; }
	inline std::shared_ptr<Shader> GetFragmentShader() const { return fragmentShader; }
};

} // namespace Junia
