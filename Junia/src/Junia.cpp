#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif

#include <Junia.hpp>
#include "Junia/Core/InternalLoggers.hpp"
#include "Platform/GLFW.hpp"
#include "Platform/Vulkan.hpp"
#include <Platform/OpenAL.hpp>
#include <Platform/OpenAL/Exception.hpp>
#include <Junia/Core/Input.hpp>
#include <Junia/Events/Events.hpp>
#include <Junia/Events/InputEvents.hpp>
#include <Junia/ECS/ECS.hpp>
#include <Junia/ECS/Components.hpp>
#include <Junia/Core/Version.hpp>
#include <Junia/Core/Time.hpp>
#include <Junia/Core/Window.hpp>
#include <Junia/Core/WindowApi.hpp>
#include <Junia/Renderer/RenderDevice.hpp>
#include <stdexcept>
#include <vector>

namespace Junia
{
	bool juniaLoopShouldStop = false;

	void Init()
	{
		Events::Register<KeyDownEvent>();
		Events::Register<KeyUpEvent>();
		Events::Register<KeyCharEvent>();
		Events::Register<MouseButtonDownEvent>();
		Events::Register<MouseButtonUpEvent>();
		Events::Register<MouseMoveEvent>();

		Events::Register<WindowClosedEvent>();

		ECS::RegisterComponent<Junia::Transform>();

#ifdef _WIN32
		// Enable ANSI Escape Sequences on Windows
		{
			HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
			DWORD dwMode;
			GetConsoleMode(hOutput, &dwMode);
			dwMode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
			SetConsoleMode(hOutput, dwMode);
		}
#endif

		// Initialize GLFW
		GLFW::Init();
		Input::Init(WindowApi::GLFW);
		InitTimer();

		try
		{
			Vulkan::Init("Testapp", Junia::Version(1, 0, 0), "Junia", Junia::Version(1, 0, 0), true);
			const std::vector<Junia::RenderDevice*>& devices = Junia::GetDevices();
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
			VKLOG_CRITICAL << "Vulkan ERROR: " << e.what();
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
		// Cleanup APIs
		Junia::Window::DestroyAll();
		Vulkan::Cleanup();
		OpenAL::Cleanup();
		GLFW::Cleanup();
	}

	void RunLoop()
	{
		while (!juniaLoopShouldStop)
		{
			Junia::Events::DispatchQueue();

			for (Junia::Window::IdType i = 1; i <= Junia::Window::GetWindowCount(); i++)
				Junia::Window::Get(i)->Update();
		}
	}

	void StopLoop()
	{
		juniaLoopShouldStop = true;
	}

	const std::vector<Junia::RenderDevice*>& GetDevices()
	{
		return Vulkan::GetDevices();
	}
}
