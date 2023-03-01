#include "Core.hpp"
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Junia/Core/Window.hpp>
#include <Junia/Core/Log.hpp>
#include <Junia/Events/Events.hpp>
#include <Junia/Events/InputEvents.hpp>
#include <Junia/Core/Input.hpp>
#include <iostream>
#include "../../Platform/Vulkan/VulkanSurface.hpp"

namespace Vulkan
{
	extern VkInstance vkInstance;
}

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

	Window::Window(const std::string& title) : title(title), nativeWindow(nullptr)
	{

	}

	Window::~Window()
	{
		Close();
	}

	void* Window::GetNative() const
	{
		return nativeWindow;
	}

	Window::IdType Window::GetID() const
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
		if (open) glfwSetWindowTitle(reinterpret_cast<GLFWwindow*>(nativeWindow), title.c_str());
	}

	JMath::iVec2 Window::GetPosition()
	{
		int x, y;
		glfwGetWindowPos(reinterpret_cast<GLFWwindow*>(nativeWindow), &x, &y);
		return { x, y };
	}

	void Window::SetPosition(JMath::iVec2 position)
	{
		glfwSetWindowPos(reinterpret_cast<GLFWwindow*>(nativeWindow), position.x, position.y);
	}

	JMath::iVec2 Window::GetSize()
	{
		int width, height;
		glfwGetWindowSize(reinterpret_cast<GLFWwindow*>(nativeWindow), &width, &height);
		return { width, height };
	}

	void Window::SetSize(JMath::iVec2 size)
	{
		glfwSetWindowSize(reinterpret_cast<GLFWwindow*>(nativeWindow), size.x, size.y);
	}

	float Window::GetOpacity()
	{
		return glfwGetWindowOpacity(reinterpret_cast<GLFWwindow*>(nativeWindow));
	}

	void Window::SetOpacity(float opacity)
	{
		glfwSetWindowOpacity(reinterpret_cast<GLFWwindow*>(nativeWindow), opacity);
	}

	bool Window::IsOpen()
	{
		return open;
	}

	void WindowFocusCallback(GLFWwindow* nativeWindow, int focused)
	{
		for (Window::IdType i = 1; i < Window::GetWindowCount() + 1; i++)
		{
			Window* window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(nativeWindow));

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
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		nativeWindow = glfwCreateWindow(800, 600, title.c_str(), NULL, NULL);
		if (nativeWindow == NULL)
		{
			const char* msg;
			glfwGetError(&msg);
			JELOG_CORE_ERROR << "Window could not be created!\n" << msg;
			return;
		}
		glfwSetWindowUserPointer(reinterpret_cast<GLFWwindow*>(nativeWindow), this);

		glfwSetWindowFocusCallback(reinterpret_cast<GLFWwindow*>(nativeWindow), WindowFocusCallback);

		index = static_cast<int>(windows.size());
		windows.push_back(this);
		if (windows[0] == nullptr) windows[0] = this;

		glfwSetKeyCallback(reinterpret_cast<GLFWwindow*>(nativeWindow), [ ] (GLFWwindow* _, const int key, int scancode, const int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
					Events::Trigger<KeyDownEvent>(static_cast<KeyCode>(GlfwToJeKey[key]));
					break;
				case GLFW_RELEASE:
					Events::Trigger<KeyUpEvent>(static_cast<KeyCode>(GlfwToJeKey[key]));
					break;
				default:
					break;
				}
			});

		glfwSetCharCallback(reinterpret_cast<GLFWwindow*>(nativeWindow), [ ] (GLFWwindow* window, unsigned int codepoint)
			{
				Events::Trigger<KeyCharEvent>(codepoint);
			});

		glfwSetMouseButtonCallback(reinterpret_cast<GLFWwindow*>(nativeWindow), [ ] (GLFWwindow* _, int button, int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
					Events::Trigger<MouseButtonDownEvent>(static_cast<MouseButton>(GlfwToJeButton[button]));
					break;
				case GLFW_RELEASE:
					Events::Trigger<MouseButtonUpEvent>(static_cast<MouseButton>(GlfwToJeButton[button]));
					break;
				default:
					break;
				}
			});

		glfwSetCursorPosCallback(reinterpret_cast<GLFWwindow*>(nativeWindow), [ ] (GLFWwindow* _, double xpos, double ypos)
			{
				Events::Trigger<MouseMoveEvent>(JMath::iVec2(static_cast<int>(xpos), static_cast<int>(ypos)));
			});

		// TODO: create vulkan surface & swapchain
		surface = new Vulkan::VulkanSurface(reinterpret_cast<GLFWwindow*>(nativeWindow));

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
		delete surface;
		glfwDestroyWindow(reinterpret_cast<GLFWwindow*>(nativeWindow));
	}

	bool Window::IsFocused()
	{
		return focused;
	}

	void Window::Focus()
	{
		glfwFocusWindow(reinterpret_cast<GLFWwindow*>(nativeWindow));
	}

	void Window::Update()
	{
		if (!open) return;
		if (glfwWindowShouldClose(reinterpret_cast<GLFWwindow*>(nativeWindow)))
		{
			Close();
			return;
		}
		/*glfwMakeContextCurrent(nativeWindow);
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glfwSwapBuffers(nativeWindow);*/
		glfwPollEvents();
	}
}
