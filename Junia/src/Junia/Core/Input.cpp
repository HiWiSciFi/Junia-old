#include "Core.hpp"
#include <Junia/Core/Input.hpp>
#include <Junia/Core/Window.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Junia
{
	static unsigned char JeToGlfwButton[3] = {
		0, 1, 2
	};

	static unsigned short JeToGlfwKey[254] = {
		  0,   0, 268, 269, 283, 282, 280, 281, 259, 258, 257,   0, 348,   0, 266, 267,
		  0,   0,   0,   0,   0,   0, 284,   0,   0,   0, 260, 256,   0,   0,   0,   0,
		 32,   0,   0,   0,   0,   0,   0,  39,   0,   0,   0,   0,  44,  45,  46,  47,
		 48,  49,  50,  51,  52,  53,  54,  55,  56,  57,   0,  59,   0,  61,   0,   0,
		  0,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
		 80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,   0,   0,
		 96, 263, 265, 262, 264, 290, 291, 292, 293, 294, 295, 296, 297, 298, 299, 300,
		301, 302, 303, 304, 305, 306, 307, 308, 309, 310, 311, 312, 313, 314,   0, 261,
		340, 344, 341, 345, 342, 346, 343, 347,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 335,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
		  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, 332, 334,   0, 333, 330, 331,
		320, 321, 322, 323, 324, 325, 326, 327, 328, 329,   0,   0,   0, 336
	};

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
