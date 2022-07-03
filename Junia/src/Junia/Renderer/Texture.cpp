#include "Texture.hpp"

#include <Junia/Renderer/Renderer.hpp>
#include <Junia/Platform/OpenGL/OpenGLTexture.hpp>
#include <Junia/Platform/Vulkan/VulkanTexture.hpp>

namespace Junia
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		case RendererAPI::API::Vulkan: return std::make_shared<VulkanTexture2D>(path);
		default: return nullptr;
		}
	}
}
