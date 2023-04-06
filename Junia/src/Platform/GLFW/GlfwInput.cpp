#include <GLFW/glfw3.h>
#include "GlfwInput.hpp"
#include <stdexcept>

namespace GLFW
{
	GlfwInput::GlfwInput()
	{

	}

	GlfwInput::~GlfwInput()
	{

	}

	bool GlfwInput::IsKeyDown_Impl(Junia::KeyCode keycode, Junia::Window::IdType window)
	{
		Junia::Window* w = Junia::Window::Get(window);
		if (w == nullptr) return false;
		const auto state = glfwGetKey(reinterpret_cast<GLFWwindow*>(w->GetNative()), JeToGlfwKey[static_cast<int>(keycode)]);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool GlfwInput::IsMouseButtonDown_Impl(Junia::MouseButton button, Junia::Window::IdType window)
	{
		Junia::Window* w = Junia::Window::Get(window);
		if (w == nullptr) return false;
		const auto state = glfwGetMouseButton(reinterpret_cast<GLFWwindow*>(w->GetNative()),
		JeToGlfwButton[static_cast<int>(button)]);
		return state == GLFW_PRESS;
	}

	JMath::Vec2i GlfwInput::GetMousePosition_Impl(Junia::Window::IdType window)
	{
		double x, y;
		Junia::Window* w = Junia::Window::Get(window);
		if (w == nullptr) return { 0, 0 };
		glfwGetCursorPos(reinterpret_cast<GLFWwindow*>(w->GetNative()), &x, &y);
		return { static_cast<int32_t>(x), static_cast<int32_t>(y) };
	}
}
