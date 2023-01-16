#ifdef _WIN32
#include <Windows.h>
#endif

#include "Junia/Core/Core.hpp"
#include <Junia.hpp>

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Platform/Vulkan/Vulkan.hpp>
#include <Platform/OpenAL/OpenAL.hpp>

namespace Junia
{
	void Init()
	{
		Events::Register<KeyDownEvent>();
		Events::Register<KeyUpEvent>();
		Events::Register<KeyCharEvent>();
		Events::Register<MouseButtonDownEvent>();
		Events::Register<MouseButtonUpEvent>();
		Events::Register<MouseMoveEvent>();

		Vulkan::Init("Testapp", 0, "Junia", 0, true);
		OpenAL::Init();

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
			JELOG_CORE_ERROR << "GLFW could not be initialized!\n" << msg;
			return;
		}
		glfwSetErrorCallback([](const int code, const char* desc)
			{
				JELOG_CORE_ERROR << "GLFW Error: (0x" << std::hex << code << ") : " << desc;
			});
	}

	void Terminate()
	{
		glfwTerminate();
	}
}
