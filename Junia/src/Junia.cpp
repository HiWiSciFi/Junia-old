#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef ERROR
#undef IGNORE
#endif

#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <JuniaScripting/Bindings_JMath.hpp>

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
#include <Junia/Core/Time.hpp>
#include <Junia/Core/Window.hpp>
#include <Junia/Core/WindowApi.hpp>
#include <Junia/Renderer/RenderDevice.hpp>
#include <stdexcept>
#include <vector>

namespace Junia
{
	const Version ENGINE_VERSION(0, 0, 0);
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

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

		JELOG_CRITICAL << "Loading mono assembly...";

		MonoDomain* domain = mono_jit_init("Junia");
		MonoAssembly* assembly = mono_domain_assembly_open(domain, "monoprogram.exe");
		if (!assembly) throw std::runtime_error("failed to open assembly");

		std::string argstr("monoprogram.exe");
		char* argv = argstr.data();
		int retval = mono_jit_exec(domain, assembly, 1, &argv);
		mono_jit_cleanup(domain);
		//Junia_Export_PrintHello();

		JELOG_CRITICAL << "Quit mono assembly";

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------

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
			Vulkan::Init("Testapp", Version(1, 0, 0), "Junia", GetEngineVersion(), true);
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

	const Version& GetEngineVersion()
	{
		return ENGINE_VERSION;
	}
}
