#pragma once

#include <Junia/Renderer/Buffer.hpp>

namespace Junia
{
	class VulkanVertexBuffer : public VertexBuffer
	{
	public:
		VulkanVertexBuffer(float* vertices, uint32_t size);
		virtual ~VulkanVertexBuffer();

		virtual void Bind()   const;
		virtual void Unbind() const;
	};

	class VulkanIndexBuffer : public IndexBuffer
	{
	public:
		VulkanIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~VulkanIndexBuffer();

		virtual void Bind()   const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() { return count; }

	private:
		uint32_t count;
	};
}
