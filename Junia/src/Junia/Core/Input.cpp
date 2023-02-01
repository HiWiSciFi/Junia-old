#include "Core.hpp"
#include <Junia/Core/Input.hpp>
#include <Junia/Core/Window.hpp>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

namespace Junia
{
	bool Input::IsKeyDown(KeyCode keycode, Window::IdType window)
	{
		Window* w = Window::GetWindow(window);
		if (w == nullptr) return false;
		const auto state = glfwGetKey(reinterpret_cast<GLFWwindow*>(w->GetNative()), JeToGlfwKey[static_cast<int>(keycode)]);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonDown(MouseButton button, Window::IdType window)
	{
		Window* w = Window::GetWindow(window);
		if (w == nullptr) return false;
		const auto state = glfwGetMouseButton(reinterpret_cast<GLFWwindow*>(w->GetNative()),
			JeToGlfwButton[static_cast<int>(button)]);
		return state == GLFW_PRESS;
	}

	std::pair<int, int> Input::GetMousePosition(Window::IdType window)
	{
		double x, y;
		Window* w = Window::GetWindow(window);
		if (w == nullptr) return { 0, 0 };
		glfwGetCursorPos(reinterpret_cast<GLFWwindow*>(w->GetNative()), &x, &y);
		return { static_cast<int>(x), static_cast<int>(y) };
	}
}
