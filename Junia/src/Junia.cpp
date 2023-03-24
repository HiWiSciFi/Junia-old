#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef ERROR
#undef IGNORE
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

		InitTimer();

		try
		{
			GLFW::Init();
			Input::Init(WindowApi::GLFW);
		}
		catch (std::exception e)
		{
			GLFWLOG_CRITICAL << "GLFW ERROR: " << e.what();
			throw e;
		}

		try
		{
			Vulkan::Init("Testapp", Junia::Version(1, 0, 0), "Junia", Junia::Version(1, 0, 0), true);
		}
		catch (std::exception e)
		{
			VKLOG_CRITICAL << "Vulkan ERROR: " << e.what();
			throw e;
		}

		try
		{
			OpenAL::Init();
		}
		catch (OpenAL::Exception e)
		{
			JECORELOG_ERROR << "OpenAL ERROR: " << e.what();
			throw e;
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
}
