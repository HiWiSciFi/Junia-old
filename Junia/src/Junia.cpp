#ifdef _WIN32
#include <Windows.h>
#endif

#include "Junia/Core/Core.hpp"
#include <Junia.hpp>

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Junia
{
	void Init()
	{
		Events::Register<KeyDownEvent>();

#ifdef _WIN32
			DWORD dwMode;
			HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
			GetConsoleMode(hOutput, &dwMode);
			dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			SetConsoleMode(hOutput, dwMode);
#endif

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
}
