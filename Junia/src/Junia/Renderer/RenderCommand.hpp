#pragma once

#include <Junia/Renderer/RendererAPI.hpp>

namespace Junia
{
	class RenderCommand
	{
	public:
		static void Init() { rendererAPI->Init(); }
		static void SetClearColor(const glm::vec4& color) { rendererAPI->SetClearColor(color); }
		static void Clear() { rendererAPI->Clear(); }

		void static DrawIndexed(const Ref<VertexArray>& vertexArray) { rendererAPI->DrawIndexed(vertexArray); }

	private:
		static RendererAPI* rendererAPI;
	};
}
