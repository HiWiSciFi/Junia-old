#include <Junia/Core/Input.hpp>

#include <stdexcept>

#include "../../Platform/GLFW/GlfwInput.hpp"

namespace Junia {

Input* Input::instance = nullptr;

void Input::Init() {
	if (instance != nullptr) return;
	instance = new GLFW::GlfwInput();
}

Input::~Input()
{ }

} // namespace Junia
