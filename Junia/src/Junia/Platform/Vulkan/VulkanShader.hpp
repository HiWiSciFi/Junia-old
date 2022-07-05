#pragma once

#include <Junia/Renderer/Shader.hpp>

namespace Junia
{
	class VulkanShader : public Shader
	{
	public:
		explicit VulkanShader(const std::string& filepath);
		VulkanShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~VulkanShader();

		void Bind() const override;
		void Unbind() const override;

		const std::string& GetName() const override { return name; }

		void UploadUniformFloat4(const std::string& name, const glm::vec4& values);
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);

	private:
		std::string name;
	};
}
