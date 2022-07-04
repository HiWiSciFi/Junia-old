#pragma once

#include <glm/glm.hpp>
#include <Junia/Renderer/VertexArray.hpp>
#include <Junia/Base.hpp>

namespace Junia
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0
			#if defined(JE_TARGETPLATFORM_WINDOWS) || defined(JE_TARGETPLATFORM_GLFW)
			, OpenGL = 1, Vulkan = 2
			#endif
		};

		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		static API GetAPI() { return api; }

	private:
		static API api;
	};
}
