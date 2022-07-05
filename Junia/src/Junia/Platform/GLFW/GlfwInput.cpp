#ifdef JE_TARGETPLATFORM_GLFW

#include "GlfwInput.hpp"

#include <GLFW/glfw3.h>
#include <Junia/Core/Application.hpp>

namespace Junia
{
	Input* Input::instance = new GlfwInput();

	bool GlfwInput::IsKeyDownImplementation(const int keycode)
	{
		const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		const auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool GlfwInput::IsMouseButtonDownImplementation(const int button)
	{
		const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		const auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<int, int> GlfwInput::GetMousePositionImplementation()
	{
		const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { static_cast<int>(x), static_cast<int>(y) };
	}
}

#endif

