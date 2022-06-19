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
	};
}
