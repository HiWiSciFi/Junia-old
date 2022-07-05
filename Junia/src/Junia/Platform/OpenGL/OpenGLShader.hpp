#pragma once

#include <Junia/Renderer/Shader.hpp>
#include <unordered_map>

typedef unsigned int GLenum;

namespace Junia
{
	class OpenGLShader : public Shader
	{
	public:
		explicit OpenGLShader(const std::string& filepath);
		OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

		[[nodiscard]] const std::string& GetName() const override { return name; }

		void UploadUniformInt(const std::string vname, int value);
		void UploadUniformFloat(const std::string vname, float value);
		void UploadUniformFloat2(const std::string vname, const glm::vec2& values);
		void UploadUniformFloat3(const std::string vname, const glm::vec3& values);
		void UploadUniformFloat4(const std::string vname, const glm::vec4& values);
		void UploadUniformMat3(const std::string vname, const glm::mat3& matrix);
		void UploadUniformMat4(const std::string vname, const glm::mat4& matrix);

	private:
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string> shaderSources);

		uint32_t rendererId = 0;
		std::string name;
	};
}
