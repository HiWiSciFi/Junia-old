#include "GlfwInput.hpp"

#include <GLFW/glfw3.h>
#include <Junia/Application.hpp>

namespace Junia
{
//#ifndef JE_TARGETPLATFORM_WINDOWS
	Input* Input::instance = new GlfwInput();
//#endif

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

	std::pair<float, float> GlfwInput::GetMousePositionImplementation()
	{
		const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return { static_cast<float>(x), static_cast<float>(y) };
	}
}
