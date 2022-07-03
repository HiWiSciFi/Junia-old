#pragma once

#include <Junia/Renderer/VertexArray.hpp>

namespace Junia
{
	class VulkanVertexArray : public VertexArray
	{
	public:
		virtual ~VulkanVertexArray() { }

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return *(new std::vector<Ref<VertexBuffer>>());  }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const override { return *(new Ref<IndexBuffer>());  }
	};
}
