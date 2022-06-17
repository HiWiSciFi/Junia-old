#pragma once

namespace Junia
{
	enum class RendererAPI
	{
		None = 0,
		OpenGL = 1,
		Vulkan = 2
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return rendererAPI; }
		static void SetAPI(RendererAPI api) { rendererAPI = api; }

	private:
		static RendererAPI rendererAPI;
	};
}
