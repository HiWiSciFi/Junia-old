#include "Texture.hpp"

#include <Junia/Renderer/Renderer.hpp>

#ifdef JE_GAPI_SUPPORTED_OPENGL
#include <Junia/Platform/OpenGL/OpenGLTexture.hpp>
#endif
#ifdef JE_GAPI_SUPPORTED_VULKAN
#include <Junia/Platform/Vulkan/VulkanTexture.hpp>
#endif

namespace Junia
{
	Ref<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
		#ifdef JE_GAPI_SUPPORTED_OPENGL
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLTexture2D>(path);
		#endif
		#ifdef JE_GAPI_SUPPORTED_VULKAN
		case RendererAPI::API::Vulkan: return std::make_shared<VulkanTexture2D>(path);
		#endif
		default: return nullptr;
		}
	}
}
