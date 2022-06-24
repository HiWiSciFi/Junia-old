#pragma once

#include <Junia/Renderer/RenderContext.hpp>
#include <Junia/Window.hpp>

namespace Junia
{
	class OpenGLRenderContext : public RenderContext
	{
	public:
		OpenGLRenderContext(Window* window);

		virtual void Init() override;
		virtual void ContextSwapBuffers() override;

	private:
		Window* window;
	};
}
