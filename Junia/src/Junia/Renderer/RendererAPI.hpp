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

		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

		static API GetAPI() { return api; }

	private:
		static API api;
	};
}
