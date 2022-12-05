#define BUILD_JUNIA
#include <Junia/Core/Window.hpp>

#include <iostream>

namespace Junia
{
	Window::Window()
	{
		window = glfwCreateWindow(800, 600, "Window", NULL, NULL);
		if (!window)
		{
			const char* msg;
			glfwGetError(&msg);
			std::cerr << "Window could not be created!" << std::endl << msg << std::endl;
			return;
		}
		glfwSetKeyCallback(window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods)
				{
					if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
					glfwSetWindowShouldClose(window, GLFW_TRUE);
				});
	}

	Window::~Window()
	{
		glfwDestroyWindow(window);
	}

	void Window::Update()
	{
		if (glfwWindowShouldClose(window))
		{
			shouldClose = true;
			return;
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}
