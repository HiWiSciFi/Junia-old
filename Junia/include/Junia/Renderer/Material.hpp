#pragma once

#include "Shader.hpp"

#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

namespace Junia {

class Material {
public:
	virtual ~Material() = 0;

	static std::shared_ptr<Material> Create(std::shared_ptr<Shader> vertexShader, std::shared_ptr<Shader> fragmentShader);

	virtual void SetVertexShader(std::shared_ptr<Shader> shader) = 0;
	virtual void SetFragmentShader(std::shared_ptr<Shader> shader) = 0;
	virtual void SetTessellationControlShader(std::shared_ptr<Shader> shader) = 0;
	virtual void SetTessellationEvaluationShader(std::shared_ptr<Shader> shader) = 0;
	virtual void SetGeometryShader(std::shared_ptr<Shader> shader) = 0;

	virtual std::shared_ptr<Shader> GetVertexShader() const = 0;
	virtual std::shared_ptr<Shader> GetFragmentShader() const = 0;
	virtual std::shared_ptr<Shader> GetTessellationControlShader() const = 0;
	virtual std::shared_ptr<Shader> GetTessellationEvaluationShader() const = 0;
	virtual std::shared_ptr<Shader> GetGeometryShader() const = 0;
};

} // namespace Juniat
