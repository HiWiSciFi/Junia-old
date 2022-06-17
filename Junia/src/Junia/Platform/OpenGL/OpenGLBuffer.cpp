#include "OpenGLBuffer.hpp"

namespace Junia
{
	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
	}

	void OpenGLVertexBuffer::Bind() const
	{
	}

	void OpenGLVertexBuffer::Unbind() const
	{
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count) : count(count)
	{
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
	}

	void OpenGLIndexBuffer::Bind() const
	{
	}

	void OpenGLIndexBuffer::Unbind() const
	{
	}
}
