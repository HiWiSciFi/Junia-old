#include "Buffer.hpp"

#include <Junia/Renderer/Renderer.hpp>

#ifdef JE_GAPI_SUPPORTED_OPENGL
#include <Junia/Platform/OpenGL/OpenGLBuffer.hpp>
#endif
#ifdef JE_GAPI_SUPPORTED_VULKAN
#include <Junia/Platform/Vulkan/VulkanBuffer.hpp>
#endif

namespace Junia
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		#ifdef JE_GAPI_SUPPORTED_OPENGL
		case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		#endif
		#ifdef JE_GAPI_SUPPORTED_VULKAN
		case RendererAPI::API::Vulkan: return new VulkanVertexBuffer(vertices, size);
		#endif
		default: return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		#ifdef JE_GAPI_SUPPORTED_OPENGL
		case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices, count);
		#endif
		#ifdef JE_GAPI_SUPPORTED_VULKAN
		case RendererAPI::API::Vulkan: return new VulkanIndexBuffer(indices, count);
		#endif
		default: return nullptr;
		}
	}
}
