#include <Junia.hpp>

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Init()
{
	if (!glfwInit())
	{
		const char* msg = nullptr;
		glfwGetError(&msg);
		std::cerr << "GLFW could not be initialized!" << std::endl << msg << std::endl;
		return;
	}
	glfwSetErrorCallback([](const int code, const char* desc)
		{
			std::cerr << "GLFW Error: (0x" << std::hex << code << ") : " << desc << std::endl;
		});
}

void Terminate()
{
	glfwTerminate();
}

void MakeWindow()
{
	GLFWwindow* window = glfwCreateWindow(800, 600, "Testwindow", nullptr, nullptr);
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

	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
}
