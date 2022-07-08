#pragma once

#include <Junia/Renderer/RenderContext.hpp>
#include <Junia/Core/Window.hpp>

#ifdef JE_TARGETPLATFORM_WINDOWS
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
		#ifdef JE_TARGETPLATFORM_WINDOWS
		Win32_HGLRC ctx = nullptr;
		[[nodiscard]] Win32_HDC GetDeviceContext() const;
		#endif
	};
}
