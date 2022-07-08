#ifdef JE_GAPI_SUPPORTED_OPENGL

#include "OpenGLRenderContext.hpp"

#include <Junia/Core/Log.hpp>
#include <glad/glad.h>

#if JE_WINDOWAPI == JE_WINDOWAPI_WIN32
#include <Junia/Platform/Windows/Win32.hpp>
#endif

#if JE_WINDOWAPI == JE_WINDOWAPI_GLFW
#include <GLFW/glfw3.h>
#endif

namespace Junia
{
	/////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////  WINDOWS  ///////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	#if JE_WINDOWAPI == JE_WINDOWAPI_WIN32
	OpenGLRenderContext::OpenGLRenderContext(Window* window) : window(window)
	{
		static bool gladInitialized = false;
		if (!gladInitialized)
		{
			Win32_HDC dc = Win32_GetDC(reinterpret_cast<Win32_HWND>(window->GetNativeWindow()));
			if (dc == nullptr)
			{
				JELOG_BASE_CRIT("Could not retrieve DeviceContext!");
				throw std::runtime_error("Could not retrieve DeviceContext!");
			}
			Win32_HGLRC dummyctx = WGL_CreateContext(dc);
			if (dummyctx == nullptr)
			{
				JELOG_BASE_CRIT("OpenGL Context could not be created!");
				throw std::runtime_error("OpenGL Context could not be created!");
			}
			if (WGL_MakeCurrent(dc, dummyctx) == false)
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

			WGL_MakeCurrent(dc, nullptr);
			WGL_DeleteContext(dummyctx);
		}
	}

	OpenGLRenderContext::~OpenGLRenderContext()
	{
		if (ctx != nullptr)
		{
			try { WGL_MakeCurrent(GetDeviceContext(), nullptr); } catch (std::exception e) { }
			WGL_DeleteContext(ctx);
		}
	}

	void OpenGLRenderContext::Init()
	{
		Win32_HDC dc = GetDeviceContext();
		if (dc == nullptr)
		{
			JELOG_BASE_CRIT("Could not retrieve DeviceContext!");
			throw std::runtime_error("Could not retrieve DeviceContext!");
		}
		ctx = WGL_CreateContext(dc);
		if (ctx == nullptr)
		{
			JELOG_BASE_CRIT("OpenGL Context could not be created!");
			throw std::runtime_error("OpenGL Context could not be created!");
		}
		if (WGL_MakeCurrent(dc, ctx) == false)
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
		if (Win32_SwapBuffers(GetDeviceContext()) == false)
		{
			JELOG_BASE_CRIT("Failed to swap buffers!");
			throw std::runtime_error("Failed to swap buffers!");
		}
	}

	Win32_HDC OpenGLRenderContext::GetDeviceContext() const
	{
		return Win32_GetDC(reinterpret_cast<Win32_HWND>(window->GetNativeWindow()));
	}
	#endif

	/////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////  GLFW  /////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////

	#if JE_WINDOWAPI == JE_WINDOWAPI_GLFW
	OpenGLRenderContext::OpenGLRenderContext(Window* window) : window(window)
	{

	}

	OpenGLRenderContext::~OpenGLRenderContext()
	{

	}

	void OpenGLRenderContext::Init()
	{
		glfwMakeContextCurrent(reinterpret_cast<GLFWwindow*>(window->GetNativeWindow()));
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status) JELOG_BASE_CRIT("failed to initialize glad!");

		JELOG_BASE_INFO("OpenGL Info:");
		JELOG_BASE_INFO("  Vendor:   " JELOG_CSTR, glGetString(GL_VENDOR));
		JELOG_BASE_INFO("  Renderer: " JELOG_CSTR, glGetString(GL_RENDERER));
		JELOG_BASE_INFO("  Version:  " JELOG_CSTR, glGetString(GL_VERSION));
	}

	void OpenGLRenderContext::ContextSwapBuffers()
	{
		glfwSwapBuffers(reinterpret_cast<GLFWwindow*>(window->GetNativeWindow()));
	}
	#endif
}

#endif
