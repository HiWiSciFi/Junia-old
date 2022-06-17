#pragma once

#include <Junia/Renderer/RenderContext.hpp>
#include <Junia/Window.hpp>

namespace Junia
{
	class OpenGLRenderContext : public RenderContext
	{
	public:
		OpenGLRenderContext(Window* window);

		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

	private:
		Window* window;
	};
}
