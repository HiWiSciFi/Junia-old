#include "GlfwInput.hpp"

#include <GLFW/glfw3.h>
#include <Junia/Application.hpp>

namespace Junia
{
	Input* Input::instance;

	bool GlfwInput::IsKeyDownImplementation(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().getNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
}
