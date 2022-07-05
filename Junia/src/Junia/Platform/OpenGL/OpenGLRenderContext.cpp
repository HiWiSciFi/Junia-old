#include "OpenGLRenderContext.hpp"

#include <Junia/Core/Log.hpp>
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
		static bool gladInitialized = false;
		if (!gladInitialized)
		{
			HDC dc = GetDC(reinterpret_cast<HWND>(window->GetNativeWindow()));
			if (dc == NULL)
			{
				JELOG_BASE_CRIT("Could not retrieve DeviceContext!");
				throw std::runtime_error("Could not retrieve DeviceContext!");
			}
			HGLRC dummyctx = wglCreateContext(dc);
			if (dummyctx == NULL)
			{
				JELOG_BASE_CRIT("OpenGL Context could not be created!");
				throw std::runtime_error("OpenGL Context could not be created!");
			}
			if (wglMakeCurrent(dc, dummyctx) == FALSE)
			{
				JELOG_BASE_CRIT("OpenGL Context could not be assigned!");
				throw std::runtime_error("OpenGL Context could not be assigned!");
			}

			if (!gladLoadGL())
			{
				JELOG_BASE_CRIT("OpenGL could not be loaded!");
				throw std::runtime_error("OpenGL could not be loaded!");
			}
			gladInitialized = true;

			wglMakeCurrent(dc, NULL);
			wglDeleteContext(dummyctx);
		}
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
		if (dc == NULL)
		{
			JELOG_BASE_CRIT("Could not retrieve DeviceContext!");
			throw std::runtime_error("Could not retrieve DeviceContext!");
		}
		ctx = wglCreateContext(dc);
		if (ctx == NULL)
		{
			JELOG_BASE_CRIT("OpenGL Context could not be created!");
			throw std::runtime_error("OpenGL Context could not be created!");
		}
		if (wglMakeCurrent(dc, ctx) == FALSE)
		{
			JELOG_BASE_CRIT("OpenGL Context could not be assigned!");
			throw std::runtime_error("OpenGL Context could not be assigned!");
		}

		JELOG_BASE_INFO("OpenGL Info:");
		JELOG_BASE_INFO("  Vendor:   " JELOG_CSTR, glGetString(GL_VENDOR));
		JELOG_BASE_INFO("  Renderer: " JELOG_CSTR, glGetString(GL_RENDERER));
		JELOG_BASE_INFO("  Version:  " JELOG_CSTR, glGetString(GL_VERSION));
	}

	void OpenGLRenderContext::ContextSwapBuffers()
	{
		if (SwapBuffers(GetDeviceContext()) == FALSE)
		{
			JELOG_BASE_CRIT("Failed to swap buffers!");
			throw std::runtime_error("Failed to swap buffers!");
		}
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
