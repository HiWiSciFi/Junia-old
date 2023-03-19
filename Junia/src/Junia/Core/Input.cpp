#include <Junia/Core/Input.hpp>
#include "../../Platform/GLFW/GlfwInput.hpp"
#include <stdexcept>

namespace Junia
{
	Input* Input::instance = nullptr;

	void Input::Init(WindowApi api)
	{
		if (instance != nullptr) return;
		switch (api)
		{
		case Junia::WindowApi::GLFW:
			instance = new GLFW::GlfwInput();
			break;
		case Junia::WindowApi::NONE:
		default: throw std::runtime_error("unknown window api");
		}
	}

	Input::~Input()
	{ }
}
