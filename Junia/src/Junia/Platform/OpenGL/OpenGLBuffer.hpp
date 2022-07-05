#pragma once

#include <Junia/Renderer/Buffer.hpp>

namespace Junia
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind()   const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return layout; }
		virtual void SetLayout(const BufferLayout& nlayout) override { layout = nlayout; }

	private:
		uint32_t rendererId = 0;
		BufferLayout layout = { };
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind()   const override;
		virtual void Unbind() const override;

		virtual uint32_t GetCount() const { return count; }

	private:
		uint32_t rendererId = 0;
		uint32_t count = 0;
	};
}
