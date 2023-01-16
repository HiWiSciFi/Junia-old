#include "Core.hpp"
#include <Junia/Core/Input.hpp>
#include <Junia/Core/Window.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Junia
{
	bool Input::IsKeyDown(KeyCode keycode, Window::IdType window)
	{
		Window* w = Window::GetWindow(window);
		if (w == nullptr) return false;
		const auto state = glfwGetKey(w->nativeWindow, JeToGlfwKey[static_cast<int>(keycode)]);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonDown(MouseButton button, Window::IdType window)
	{
		Window* w = Window::GetWindow(window);
		if (w == nullptr) return false;
		const auto state = glfwGetMouseButton(w->nativeWindow,
			JeToGlfwButton[static_cast<int>(button)]);
		return state == GLFW_PRESS;
	}

	std::pair<int, int> Input::GetMousePosition(Window::IdType window)
	{
		double x, y;
		Window* w = Window::GetWindow(window);
		if (w == nullptr) return { 0, 0 };
		glfwGetCursorPos(w->nativeWindow, &x, &y);
		return { static_cast<int>(x), static_cast<int>(y) };
	}
}
