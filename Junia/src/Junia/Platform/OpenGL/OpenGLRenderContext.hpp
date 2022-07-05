#pragma once

#include <Junia/Renderer/RenderContext.hpp>
#include <Junia/Core/Window.hpp>

#ifdef JE_TARGETPLATFORM_WINDOWS
#include <Windows.h>
#endif

namespace Junia
{
	class OpenGLRenderContext : public RenderContext
	{
	public:
		OpenGLRenderContext(Window* window);
		~OpenGLRenderContext();

		virtual void Init() override;
		virtual void ContextSwapBuffers() override;

	private:
		Window* window = nullptr;
		#ifdef JE_TARGETPLATFORM_WINDOWS
		HGLRC ctx = nullptr;
		HDC GetDeviceContext() const;
		#endif
	};
}
