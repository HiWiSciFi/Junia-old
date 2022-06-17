#pragma once

#include <Junia/Renderer/Buffer.hpp>

namespace Junia
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind()   const;
		virtual void Unbind() const;

	private:
		uint32_t rendererId;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind()   const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return count; }

	private:
		uint32_t rendererId;
		uint32_t count;
	};
}
