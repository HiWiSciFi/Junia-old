#ifdef _WIN32
#include <Windows.h>
#endif

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "Junia/Core/Core.hpp"
#include <Junia.hpp>

#include <Platform/Vulkan.hpp>
#include <Platform/Vulkan/Exception.hpp>

#include <Platform/OpenAL.hpp>
#include <Platform/OpenAL/Exception.hpp>

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

		try
		{
			Vulkan::Init("Testapp", Junia::Version(1, 0, 0), "Junia", Junia::Version(1, 0, 0), true);
			OpenAL::Init();
		}
		catch (Vulkan::Exception e)
		{
			JELOG_ERROR << "Vulkan ERROR: " << e.what();
		}
		catch (OpenAL::Exception e)
		{
			JELOG_ERROR << "OpenAL ERROR: " << e.what();
		}
	}

	void Terminate()
	{
		glfwTerminate();
	}
}
