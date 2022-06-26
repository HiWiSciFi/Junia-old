#pragma once

#include <Junia/Renderer/RendererAPI.hpp>

namespace Junia
{
	class RenderCommand
	{
	public:
		static void SetClearColor(const glm::vec4& color) { rendererAPI->SetClearColor(color); }
		static void Clear() { rendererAPI->Clear(); }

		void static DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) { rendererAPI->DrawIndexed(vertexArray); }

	private:
		static RendererAPI* rendererAPI;
	};
}
