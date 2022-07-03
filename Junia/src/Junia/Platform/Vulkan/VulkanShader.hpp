#pragma once

#include <Junia/Renderer/Shader.hpp>

namespace Junia
{
	class VulkanShader : public Shader
	{
	public:
		VulkanShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~VulkanShader();

		void Bind() const;
		void Unbind() const;

		void UploadUniformFloat4(const std::string name, const glm::vec4& values);
		void UploadUniformMat4(const std::string name, const glm::mat4& matrix);
	};
}
