#include <Junia/Core/Window.hpp>

#include <vector>

#include "../../Platform/GLFW/GlfwWindow.hpp"

namespace Junia {

std::vector<Window*> windows{ nullptr };

void Window::SwapIds(IdType id1, IdType id2) {
	if (id1 == id2 || id1 <= 0 || id2 <= 0) return;
	Window* w1 = windows[id1];
	windows[id1] = windows[id2];
	windows[id2] = w1;
	windows[id1]->id = id1;
	windows[id2]->id = id2;
}

std::size_t Window::GetWindowCount() {
	return windows.size() - 1;
}

Window** Window::GetAll() {
	return windows.data() + 1;
}

bool Window::Exists(IdType id) {
	return windows.size() > id && windows.size() > 1 && id > 0;
}

bool Window::Exists(Window* window) {
	for (std::size_t i = 1; i < windows.size(); i++)
		if (windows[i] == window) return true;
	return false;
}

Window* Window::Get(IdType id) {
	if (id == 0) return windows[0];
	if (!Exists(id)) return nullptr;
	return windows[id];
}

std::shared_ptr<Window> Window::Create(const std::string& title, int width, int height) {
	return std::make_shared<GLFW::GlfwWindow>(title, width, height);
}

void Window::Destroy(Window* window) {
	delete window;
}

void Window::Destroy(IdType id) {
	delete windows[id];
}

void Window::DestroyAll() {
	while (windows.size() > 1) delete windows[windows.size() - 1];
}

Window::~Window() { }

} // namespace Junia
