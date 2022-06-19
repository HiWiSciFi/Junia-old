#include "OpenGLRenderContext.hpp"

#include <Junia/Log.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Junia
{
	OpenGLRenderContext::OpenGLRenderContext(Window* window) : window(window)
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

	void OpenGLRenderContext::SwapBuffers()
	{
		glfwSwapBuffers(static_cast<GLFWwindow*>(window->GetNativeWindow()));
	}
}
