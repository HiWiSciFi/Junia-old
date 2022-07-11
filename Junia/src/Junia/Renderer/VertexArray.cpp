#include "VertexArray.hpp"

#include <Junia/Renderer/Renderer.hpp>

#ifdef JE_GAPI_SUPPORTED_OPENGL
#include <Junia/Platform/OpenGL/OpenGLVertexArray.hpp>
#endif
#ifdef JE_GAPI_SUPPORTED_VULKAN
#include <Junia/Platform/Vulkan/VulkanVertexArray.hpp>
#endif

namespace Junia
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		#ifdef JE_GAPI_SUPPORTED_OPENGL
		case RendererAPI::API::OpenGL: return std::make_shared<OpenGLVertexArray>();
		#endif
		#ifdef JE_GAPI_SUPPORTED_VULKAN
		case RendererAPI::API::Vulkan: return std::make_shared<VulkanVertexArray>();
		#endif
		default: return nullptr;
		}
	}
}
