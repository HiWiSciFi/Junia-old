#pragma once

#include <Junia/Renderer/VertexArray.hpp>

namespace Junia
{
	class VulkanVertexArray : public VertexArray
	{
	public:
		virtual ~VulkanVertexArray() { }

		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(Ref<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;

		[[nodiscard]] const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return *(new std::vector<Ref<VertexBuffer>>());  }
		[[nodiscard]] const Ref<IndexBuffer>& GetIndexBuffer() const override { return *(new Ref<IndexBuffer>());  }
	};
}
