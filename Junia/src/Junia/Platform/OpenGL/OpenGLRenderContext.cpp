#include "OpenGLRenderContext.hpp"

#include <Junia/Log.hpp>
#include <glad/glad.h>

#ifdef JE_TARGETPLATFORM_WINDOWS
#include <Windows.h>
#endif

#ifdef JE_TARGETPLATFORM_GLFW
#include <GLFW/glfw3.h>
#endif

namespace Junia
{
	/////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////  WINDOWS  ///////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	#ifdef JE_TARGETPLATFORM_WINDOWS
	OpenGLRenderContext::OpenGLRenderContext(Window* window) : window(window)
	{

	}

	OpenGLRenderContext::~OpenGLRenderContext()
	{
		if (ctx != nullptr)
		{
			try { wglMakeCurrent(GetDeviceContext(), NULL); } catch (std::exception e) { }
			wglDeleteContext(ctx);
		}
	}

	void OpenGLRenderContext::Init()
	{
		HDC dc = GetDeviceContext();
		static bool gladInitialized = false;
		if (!gladInitialized)
		{
			HGLRC dummyctx = wglCreateContext(dc);
			wglMakeCurrent(dc, dummyctx);

			if (!gladLoadGL())
			{
				JELOG_BASE_CRIT("OpenGL could not be loaded!");
				throw std::runtime_error("OpenGL could not be loaded!");
			}
			gladInitialized = true;

			wglMakeCurrent(dc, NULL);
			wglDeleteContext(dummyctx);
		}
		ctx = wglCreateContext(dc);
		wglMakeCurrent(dc, ctx);

		JELOG_BASE_INFO("OpenGL Info:");
		JELOG_BASE_INFO("  Vendor:   " JELOG_CSTR, glGetString(GL_VENDOR));
		JELOG_BASE_INFO("  Renderer: " JELOG_CSTR, glGetString(GL_RENDERER));
		JELOG_BASE_INFO("  Version:  " JELOG_CSTR, glGetString(GL_VERSION));
	}

	void OpenGLRenderContext::ContextSwapBuffers()
	{
		SwapBuffers(GetDeviceContext());
	}

	HDC OpenGLRenderContext::GetDeviceContext() const
	{
		return GetDC(static_cast<HWND>(window->GetNativeWindow()));
	}
	#endif

	/////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////  GLFW  /////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	#ifdef JE_TARGETPLATFORM_GLFW
	OpenGLRenderContext::OpenGLRenderContext(Window* window) : window(window)
	{

	}

	OpenGLRenderContext::~OpenGLRenderContext()
	{

	}

	void OpenGLRenderContext::Init()
	{
		glfwMakeContextCurrent(static_cast<GLFWwindow*>(window->GetNativeWindow()));
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status) JELOG_BASE_CRIT("failed to initialize glad!");

		JELOG_BASE_INFO("OpenGL Info:");
		JELOG_BASE_INFO("  Vendor:   " JELOG_CSTR, glGetString(GL_VENDOR));
		JELOG_BASE_INFO("  Renderer: " JELOG_CSTR, glGetString(GL_RENDERER));
		JELOG_BASE_INFO("  Version:  " JELOG_CSTR, glGetString(GL_VERSION));
	}

	void OpenGLRenderContext::ContextSwapBuffers()
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(window->GetNativeWindow()));
	}
	#endif
}
