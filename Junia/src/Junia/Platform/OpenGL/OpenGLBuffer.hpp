#pragma once

#include <Junia/Renderer/Buffer.hpp>

namespace Junia
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		~OpenGLVertexBuffer() override;

		void Bind()   const override;
		void Unbind() const override;

		[[nodiscard]] const BufferLayout& GetLayout() const override { return layout; }
		void SetLayout(const BufferLayout& nlayout) override { layout = nlayout; }

	private:
		uint32_t rendererId = 0;
		BufferLayout layout = { };
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer() override;

		void Bind()   const override;
		void Unbind() const override;

		[[nodiscard]] uint32_t GetCount() const override { return count; }

	private:
		uint32_t rendererId = 0;
		uint32_t count = 0;
	};
}
