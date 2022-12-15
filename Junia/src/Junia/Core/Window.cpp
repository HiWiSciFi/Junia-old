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
		if (id >= windows.size() || id < 0) return nullptr;
		return windows.at(id);
	}

	Window* Window::GetWindow()
	{
		return GetWindow(0);
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
		Close();
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

	JMath::iVec2 Window::GetPosition()
	{
		int x, y;
		glfwGetWindowPos(nativeWindow, &x, &y);
		return { x, y };
	}

	void Window::SetPosition(JMath::iVec2 position)
	{
		glfwSetWindowPos(nativeWindow, position.x, position.y);
	}

	JMath::iVec2 Window::GetSize()
	{
		int width, height;
		glfwGetWindowSize(nativeWindow, &width, &height);
		return { width, height };
	}

	void Window::SetSize(JMath::iVec2 size)
	{
		glfwSetWindowSize(nativeWindow, size.x, size.y);
	}

	float Window::GetOpacity()
	{
		return glfwGetWindowOpacity(nativeWindow);
	}

	void Window::SetOpacity(float opacity)
	{
		glfwSetWindowOpacity(nativeWindow, opacity);
	}

	bool Window::IsOpen()
	{
		return open;
	}

	static void WindowFocusCallback(GLFWwindow* nativeWindow, int focused)
	{
		for (Window::IdType i = 1; i < Window::GetWindowCount() + 1; i++)
		{
			Window* window = Window::GetWindow(i);
			if (window == nullptr || window->nativeWindow != nativeWindow) continue;

			if (focused) Window::GetWindows()[0] = window;
			else if (Window::GetWindows()[0] == window) Window::GetWindows()[0] = nullptr;

			window->focused = focused;
			break;
		}
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
		glfwSetWindowFocusCallback(nativeWindow, WindowFocusCallback);
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
		focused = false;
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

	bool Window::IsFocused()
	{
		return focused;
	}

	void Window::Focus()
	{
		glfwFocusWindow(nativeWindow);
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
