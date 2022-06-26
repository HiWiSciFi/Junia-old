#include "VertexArray.hpp"

#include <Junia/Renderer/Renderer.hpp>
#include <Junia/Platform/OpenGL/OpenGLVertexArray.hpp>
#include <Junia/Platform/Vulkan/VulkanVertexArray.hpp>

namespace Junia
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
		case RendererAPI::API::Vulkan: return new VulkanVertexArray();
		default: return nullptr;
		}
	}
}
