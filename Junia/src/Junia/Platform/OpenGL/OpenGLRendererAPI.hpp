#pragma once

#include <Junia/Renderer/RendererAPI.hpp>
#include <Junia/Base.hpp>

namespace Junia
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}
