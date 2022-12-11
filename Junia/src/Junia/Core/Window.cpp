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

	Window* Window::GetWindow(Window::IdType id)
	{
		return windows.at(id);
	}

	Window* Window::Create(const std::string& title)
	{
		return new Window(title);
	}

	void Window::Destroy(Window::IdType id)
	{
		Destroy(GetWindow(id));
	}

	void Window::Destroy(const Window* window)
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
			JELOG_CORE_TRACE << "  Vendor:       " << glGetString(GL_VENDOR);
			JELOG_CORE_TRACE << "  Renderer:     " << glGetString(GL_RENDERER);
			JELOG_CORE_TRACE << "  Version:      " << glGetString(GL_VERSION);
			JELOG_CORE_TRACE << "  GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION);
		}
	}

	Window::Window(const std::string& title) : title(title), nativeWindow(nullptr)
	{
		
	}

	Window::~Window()
	{
		if (open) Close();
	}

	Window::IdType Window::GetID()
	{
		return index;
	}

	const std::string& Window::GetTitle()
	{
		return title;
	}

	void Window::SetTitle(const std::string& title)
	{
		this->title = title;
		if (open) glfwSetWindowTitle(nativeWindow, title.c_str());
	}

	bool Window::IsOpen()
	{
		return open;
	}

	void Window::Open()
	{
		if (open) return;
		index = -1;
		nativeWindow = glfwCreateWindow(800, 600, title.c_str(), NULL, NULL);
		if (nativeWindow == NULL)
		{
			const char* msg;
			glfwGetError(&msg);
			JELOG_CORE_ERROR << "Window could not be created!\n" << msg;
			return;
		}
		index = static_cast<int>(windows.size());
		windows.push_back(this);
		if (windows[0] == nullptr) windows[0] = this;

		glfwMakeContextCurrent(nativeWindow);
		if (!gladStatus) LoadGlad();
		open = true;
	}

	void Window::Close()
	{
		if (!open) return;
		open = false;

		int lastIndex = GetWindowCount();
		if (lastIndex != index)
		{
			windows[index] = windows[lastIndex];
			windows[index]->index = index;
		}
		index = -1;
		windows.pop_back();
		glfwDestroyWindow(nativeWindow);
	}

	void Window::Update()
	{
		if (!open) return;
		if (glfwWindowShouldClose(nativeWindow))
		{
			Close();
			return;
		}
		glfwMakeContextCurrent(nativeWindow);
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glfwSwapBuffers(nativeWindow);
		glfwPollEvents();
	}
}
