#include <Junia.hpp>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>
#include <GLFW/glfw3.h>

int add(int a, int b)
{
	return a + b;
}

int subtract(int a, int b)
{
	return a - b;
}

void MakeWindow()
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

	GLFWwindow* window = glfwCreateWindow(800, 600, "Testwindow", nullptr, nullptr);

	#ifdef _WIN32
	Sleep(5000);
	#else
	sleep(5);
	#endif

	glfwDestroyWindow(window);
	glfwTerminate();
	std::cout << "done" << std::endl;
}
