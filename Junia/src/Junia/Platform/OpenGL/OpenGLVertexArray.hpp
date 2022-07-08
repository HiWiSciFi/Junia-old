#pragma once

#ifdef JE_GAPI_SUPPORTED_OPENGL

#include <Junia/Renderer/VertexArray.hpp>

namespace Junia
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(Ref<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		[[nodiscard]] const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return vertexBuffers; }
		[[nodiscard]] const Ref<IndexBuffer>& GetIndexBuffer() const override { return indexBuffer; }

	private:
		uint32_t rendererId = 0;
		std::vector<Ref<VertexBuffer>> vertexBuffers { };
		Ref<IndexBuffer> indexBuffer { };
	};
}

#endif
