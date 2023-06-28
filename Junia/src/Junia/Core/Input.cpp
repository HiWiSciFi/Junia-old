#include <Junia/Core/Input.hpp>
#include "../../Platform/GLFW/GlfwInput.hpp"
#include <stdexcept>

namespace Junia
{
	Input* Input::instance = nullptr;

	void Input::Init()
	{
		if (instance != nullptr) return;
		instance = new GLFW::GlfwInput();
	}

	Input::~Input()
	{ }
}
