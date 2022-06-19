#pragma once

#include <Junia/Renderer/Shader.hpp>

namespace Junia
{
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~OpenGLShader();

		void Bind() const;
		void Unbind() const;

	private:
		uint32_t rendererId;
	};
}
