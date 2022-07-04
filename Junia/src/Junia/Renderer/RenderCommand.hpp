#pragma once

#include <Junia/Renderer/RendererAPI.hpp>

namespace Junia
{
	class RenderCommand
	{
	public:
		static void Init() { rendererAPI->Init(); }
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) { rendererAPI->SetViewport(x, y, width, height); }
		static void SetClearColor(const glm::vec4& color) { rendererAPI->SetClearColor(color); }
		static void Clear() { rendererAPI->Clear(); }

		void static DrawIndexed(const Ref<VertexArray>& vertexArray) { rendererAPI->DrawIndexed(vertexArray); }

	private:
		static RendererAPI* rendererAPI;
	};
}
