#pragma once

#ifdef JE_GAPI_SUPPORTED_VULKAN

#include <Junia/Renderer/Buffer.hpp>
#include <vulkan/vulkan.h>

namespace Junia
{
	class VulkanVertexBuffer : public VertexBuffer
	{
	public:
		VulkanVertexBuffer(float* vertices, uint32_t size);
		virtual ~VulkanVertexBuffer();

		virtual void Bind()   const;
		virtual void Unbind() const;

		virtual const BufferLayout& GetLayout() const override { return layout; }
		virtual void SetLayout(const BufferLayout& nlayout) override { layout = nlayout; }

	private:
		VkDevice device = nullptr;
		VkBuffer vkBuf = nullptr;
		BufferLayout layout;
	};

	class VulkanIndexBuffer : public IndexBuffer
	{
	public:
		VulkanIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~VulkanIndexBuffer();

		virtual void Bind()   const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return count; }

	private:
		uint32_t count = 0;
		VkDevice device = nullptr;
		VkBuffer vkBuf = nullptr;
	};
}

#endif
