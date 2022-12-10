#include "Core.hpp"
#include <Junia/Core/Window.hpp>
#include <Junia/Core/Log.hpp>
#include <iostream>

namespace Junia
{
	std::vector<Window*> Window::windows{ nullptr };

	int Window::GetWindowCount()
	{
		return static_cast<int>(windows.size() - 1);
	}

	Window** const Window::GetWindows()
	{
		return windows.data();
	}

	Window* Window::GetWindow(int id)
	{
		return windows.at(id);
	}

	Window* Window::CreateWindow()
	{
		return new Window();
	}

	void Window::DestroyWindow(int id)
	{
		DestroyWindow(GetWindow(id));
	}

	void Window::DestroyWindow(const Window* window)
	{
		delete window;
	}

	static int gladStatus = 0;
	static void LoadGlad()
	{
		gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!gladStatus)
		{
			JELOG_CORE_CRITICAL << "OpenGL could not be initialized!";
		}
		else
		{
			JELOG_CORE_TRACE << "OpenGL Info:";
			JELOG_CORE_TRACE << "  Vendor:   " << glGetString(GL_VENDOR);
			JELOG_CORE_TRACE << "  Renderer: " << glGetString(GL_RENDERER);
			JELOG_CORE_TRACE << "  Version:  " << glGetString(GL_VERSION);
		}
	}

	Window::Window()
	{
		index = -1;
		nativeWindow = glfwCreateWindow(800, 600, "Window", NULL, NULL);
		if (!nativeWindow)
		{
			const char* msg;
			glfwGetError(&msg);
			JELOG_CORE_ERROR << "Window could not be created!\n" << msg;
			return;
		}
		glfwSetKeyCallback(nativeWindow,
			[](GLFWwindow* window, int key, int scancode, int action, int mods)
				{
					if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
					glfwSetWindowShouldClose(window, GLFW_TRUE);
				});
		index = static_cast<int>(windows.size());
		windows.push_back(this);
		if (windows[0] == nullptr) windows[0] = this;

		glfwMakeContextCurrent(nativeWindow);
		if (!gladStatus) LoadGlad();
	}

	Window::~Window()
	{
		int lastIndex = GetWindowCount();
		if (lastIndex != index)
		{
			windows[index] = windows[lastIndex];
			windows[index]->index = index;
		}
		windows.pop_back();
		glfwDestroyWindow(nativeWindow);
	}

	void Window::Open()
	{

	}

	void Window::Close()
	{

	}

	int Window::GetID()
	{
		return index;
	}

	void Window::Update()
	{
		if (glfwWindowShouldClose(nativeWindow))
		{
			shouldClose = true;
			return;
		}
		glfwMakeContextCurrent(nativeWindow);
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glfwSwapBuffers(nativeWindow);
		glfwPollEvents();
	}
}
