#ifdef _WIN32
#include <Windows.h>
#endif

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <Junia.hpp>
#include "Junia/Core/InternalLoggers.hpp"

#include <Platform/Vulkan.hpp>

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

		Input::Init(WindowApi::GLFW);

		glfwSetErrorCallback([](const int code, const char* desc)
			{
				JECORELOG_ERROR << "GLFW Error: (0x" << std::hex << code << ") : " << desc;
			});

		try
		{
			Vulkan::Init("Testapp", Junia::Version(1, 0, 0), "Junia", Junia::Version(1, 0, 0), true);
			std::vector<Junia::RenderDevice*>& devices = Vulkan::GetDevices();
			JECORELOG_INFO << "Available Render devices:";
			for (const auto& d : devices)
			{
				Junia::Log::Logstream logMsg = JECORELOG_INFO;
				logMsg << "  - " << d->GetName() << " | Rating: " << d->GetRating() << " | Type: ";
				switch (d->GetType())
				{
				case Junia::RenderDeviceType::CPU: logMsg << "CPU"; break;
				case Junia::RenderDeviceType::INTEGRATED_GPU: logMsg << "Integrated GPU"; break;
				case Junia::RenderDeviceType::VIRTUAL_GPU: logMsg << "Virtual GPU"; break;
				case Junia::RenderDeviceType::DISCRETE_GPU: logMsg << "Discrete GPU"; break;
				case Junia::RenderDeviceType::OTHER:
				default: logMsg << "Other"; break;
				}
			}
			Vulkan::PickDevice(nullptr);
		}
		catch (std::exception e)
		{
			JECORELOG_ERROR << "Vulkan ERROR: " << e.what();
			throw std::runtime_error(e.what());
		}

		try
		{
			OpenAL::Init();
		}
		catch (OpenAL::Exception e)
		{
			JECORELOG_ERROR << "OpenAL ERROR: " << e.what();
		}
	}

	void Terminate()
	{
		Vulkan::Cleanup();
	}
}
