#include <Junia/Core/Window.hpp>
#include <Junia/Events/Events.hpp>
#include <Junia/Events/InputEvents.hpp>
#include <Junia/Core/Input.hpp>
#include "../../Platform/GLFW/GlfwWindow.hpp"

namespace Junia
{
	std::vector<Window*> windows{ nullptr };

	void Window::SwapWindowIds(IdType id1, IdType id2)
	{
		if (id1 == id2) return;
		Window* w1 = windows[id1];
		windows[id1] = windows[id2];
		windows[id2] = w1;
		windows[id1]->id = id1;
		windows[id2]->id = id2;
	}

	size_t Window::GetWindowCount()
	{
		return windows.size() - 1;
	}

	Window** Window::GetWindows()
	{
		return windows.data() + 1;
	}

	bool Window::WindowExists(IdType id)
	{
		return windows.size() < id && windows.size() > 1;
	}

	bool Window::WindowExists(Window* window)
	{
		for (size_t i = 1; i < windows.size(); i++)
			if (windows[i] == window) return true;
		return false;
	}

	Window* Window::GetWindow(IdType id)
	{
		return windows[id];
	}

	Window* Window::Create(const std::string& title, int width, int height)
	{
		return new GLFW::GlfwWindow(title, width, height);
	}

	void Window::Destroy(Window* window)
	{
		delete window;
	}

	void Window::Destroy(IdType id)
	{
		delete windows[id];
	}

	Window::~Window()
	{

	}
}
