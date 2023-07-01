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
#include <stdexcept>
#include <vector>

namespace Junia {

const Version ENGINE_VERSION(0, 0, 0);
bool juniaLoopShouldStop = false;

static std::shared_ptr<RendererSystem> renderer = nullptr;

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

	ECS::RegisterComponent<Transform>();
	ECS::RegisterComponent<MeshRenderer>();

	renderer = ECS::RegisterSystem<RendererSystem>();

	// Enable ANSI Escape Sequences on Windows
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
	// Cleanup APIs
	Junia::ECS::Entity::DestroyAll();
	Junia::Window::DestroyAll();
	Vulkan::Cleanup();
	OpenAL::Cleanup();
	GLFW::Cleanup();
}

void RunLoop() {
	while (!juniaLoopShouldStop) {
		try {
			Junia::Events::DispatchQueue();

			renderer->Update(0);

			for (Junia::Window::IdType i = 1; i <= Junia::Window::GetWindowCount(); i++)
				Junia::Window::Get(i)->Update();
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
