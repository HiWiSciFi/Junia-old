#include "Shader.hpp"

#include <Junia/Renderer/Renderer.hpp>

#include <Junia/Platform/OpenGL/OpenGLShader.hpp>
#include <Junia/Platform/Vulkan/VulkanShader.hpp>

namespace Junia
{
	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::OpenGL: return new OpenGLShader(vertexSrc, fragmentSrc);
		case RendererAPI::Vulkan: return new VulkanShader(vertexSrc, fragmentSrc);
		default: return nullptr;
		}
	}
}
