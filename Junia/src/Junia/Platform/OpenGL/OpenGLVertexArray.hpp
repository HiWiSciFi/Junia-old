#pragma once

#include <Junia/Renderer/VertexArray.hpp>

namespace Junia
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return vertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return indexBuffer; }

	private:
		uint32_t rendererId = 0;
		std::vector<Ref<VertexBuffer>> vertexBuffers { };
		Ref<IndexBuffer> indexBuffer { };
	};
}
