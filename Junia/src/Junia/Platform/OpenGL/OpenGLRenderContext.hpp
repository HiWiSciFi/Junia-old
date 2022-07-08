#pragma once

#ifdef JE_GAPI_SUPPORTED_OPENGL

#include <Junia/Renderer/RenderContext.hpp>
#include <Junia/Core/Window.hpp>

#if JE_WINDOWAPI == JE_WINDOWAPI_WIN32
#include <Junia/Platform/Windows/Win32.hpp>
#endif

namespace Junia
{
	class OpenGLRenderContext : public RenderContext
	{
	public:
		explicit OpenGLRenderContext(Window* window);
		~OpenGLRenderContext() override;

		void Init() override;
		void ContextSwapBuffers() override;

	private:
		Window* window = nullptr;
		#if JE_WINDOWAPI == JE_WINDOWAPI_WIN32
		Win32_HGLRC ctx = nullptr;
		[[nodiscard]] Win32_HDC GetDeviceContext() const;
		#endif
	};
}

#endif
