#include "Buffer.hpp"

#include <Junia/Renderer/Renderer.hpp>

#include <Junia/Platform/OpenGL/OpenGLBuffer.hpp>
#include <Junia/Platform/Vulkan/VulkanBuffer.hpp>

namespace Junia
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::OpenGL: return new OpenGLVertexBuffer(vertices, size);
		case RendererAPI::Vulkan: return new VulkanVertexBuffer(vertices, size);
		default: return nullptr;
		}
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::OpenGL: return new OpenGLIndexBuffer(indices, count);
		case RendererAPI::Vulkan: return new VulkanIndexBuffer(indices, count);
		default: return nullptr;
		}
	}
}
