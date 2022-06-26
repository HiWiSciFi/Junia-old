#pragma once

#include <Junia/Renderer/Shader.hpp>

namespace Junia
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		void Bind() const override;
		void Unbind() const override;

		void UploadUniformMat4(const std::string name, const glm::mat4& matrix) override;

	private:
		uint32_t rendererId;
	};
}
