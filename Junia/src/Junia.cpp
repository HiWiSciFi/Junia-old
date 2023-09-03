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
#include "Platform/OpenAL.hpp"
#include <Junia/Core/Input.hpp>
#include <Junia/Events/Events.hpp>
#include <Junia/Events/InputEvents.hpp>
#include <Junia/ECS/ECS.hpp>
#include <Junia/ECS/Components.hpp>
#include <Junia/ECS/Systems.hpp>
#include <Junia/Core/Time.hpp>
#include <Junia/Core/Window.hpp>
#include <Junia/Renderer/RenderDevice.hpp>
#include <chrono>
#include <stdexcept>
#include <vector>

namespace Junia {

const Version ENGINE_VERSION(0, 0, 0);
bool juniaLoopShouldStop = false;

static void WindowsEnableANSI() {
#ifdef _WIN32
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hOutput, &mode);
	mode |= ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOutput, mode);
#endif
}

void Init() {
	Events::Register<KeyDownEvent>();
	Events::Register<KeyUpEvent>();
	Events::Register<KeyCharEvent>();
	Events::Register<MouseButtonDownEvent>();
	Events::Register<MouseButtonUpEvent>();
	Events::Register<MouseMoveEvent>();

	Events::Register<WindowClosedEvent>();

	WindowsEnableANSI();

	InitTimer();

	try {
		GLFW::Init();
		Input::Init();
	} catch (std::exception e) {
		GLFWLOG_CRITICAL << "GLFW ERROR: " << e.what();
		throw e;
	}

	try {
#ifndef NDEBUG
		Vulkan::Init("Testapp", Version(1, 0, 0), "Junia", GetEngineVersion(), true);
#else
		Vulkan::Init("Testapp", Version(1, 0, 0), "Junia", GetEngineVersion(), false);
#endif
	} catch (std::exception e) {
		VKLOG_CRITICAL << "Vulkan ERROR: " << e.what();
		throw e;
	}

	try {
		OpenAL::Init();
	} catch (std::exception e) {
		JECORELOG_ERROR << "OpenAL ERROR: " << e.what();
		throw e;
	}
}

void Terminate() {
	Window::DestroyAll();
	Vulkan::Cleanup();
	OpenAL::Cleanup();
	GLFW::Cleanup();
}

void RunLoop() {
	float delta = std::numeric_limits<float>::epsilon();
	std::chrono::high_resolution_clock::time_point endtime, starttime = std::chrono::high_resolution_clock::now();
	while (!juniaLoopShouldStop) {
		try {
			Events::DispatchQueue();
			for (Window::IdType i = 1; i <= Window::GetWindowCount(); i++) Window::Get(i)->Update(delta);

			endtime = std::chrono::high_resolution_clock::now();
			delta = std::chrono::duration<float, std::chrono::seconds::period>(endtime - starttime).count();
			if (delta <= 0.0f) delta = std::numeric_limits<float>::epsilon();
			starttime = endtime;
		} catch (std::exception e) {
			JECORELOG_CRITICAL << "Exception thrown: " << e.what();
			throw e;
		}
	}
}

void StopLoop() {
	juniaLoopShouldStop = true;
}

const Version& GetEngineVersion() {
	return ENGINE_VERSION;
}

} // namespace Junia
