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

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override { return *(new std::vector<std::shared_ptr<VertexBuffer>>());  }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return *(new std::shared_ptr<IndexBuffer>());  }
	};
}
