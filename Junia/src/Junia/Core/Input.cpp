#include "Core.hpp"
#include <Junia/Core/Input.hpp>
#include <Junia/Core/Window.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Junia
{
	bool Input::IsKeyDown(const int keycode, uint32_t window)
	{
		const auto state = glfwGetKey(Window::GetWindow(window)->nativeWindow, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonDown(const int button, uint32_t window)
	{
		const auto state = glfwGetMouseButton(Window::GetWindow(window)->nativeWindow, button);
		return state == GLFW_PRESS;
	}

	std::pair<int, int> Input::GetMousePosition(uint32_t window)
	{
		double x, y;
		glfwGetCursorPos(Window::GetWindow(window)->nativeWindow, &x, &y);
		return { static_cast<int>(x), static_cast<int>(y) };
	}
}
