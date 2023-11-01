#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef ERROR
#undef IGNORE
#endif

#include <Junia.hpp>
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

#include "Junia/Core/InternalLoggers.hpp"
#include "Platform/GLFW.hpp"
#include "Platform/Vulkan/Instance.hpp"

// TODO: remove
//#include <spirv_reflect.h>

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

void Init(const std::string& appName, Version appVersion) {
	Events::Register<KeyDownEvent>();
	Events::Register<KeyUpEvent>();
	Events::Register<KeyCharEvent>();
	Events::Register<MouseButtonDownEvent>();
	Events::Register<MouseButtonUpEvent>();
	Events::Register<MouseMoveEvent>();

	Events::Register<WindowClosedEvent>();

	WindowsEnableANSI();

	InitTimer();

	// TODO: remove
	/*{
		std::vector<std::uint8_t> spv = ReadFileBinary("res/Shaders/shader2.vert.spv");
		SpvReflectShaderModule module;
		SpvReflectResult result = spvReflectCreateShaderModule(spv.size(), spv.data(), &module);
		if (result != SPV_REFLECT_RESULT_SUCCESS) throw std::runtime_error("failed to load spv");

		std::uint32_t var_count = 0;
		result = spvReflectEnumerateInputVariables(&module, &var_count, NULL);
		if (result != SPV_REFLECT_RESULT_SUCCESS) throw std::runtime_error("failed to enumerate variables");
		std::vector<SpvReflectInterfaceVariable*> input_vars(var_count);
		result = spvReflectEnumerateInputVariables(&module, &var_count, input_vars.data());
		if (result != SPV_REFLECT_RESULT_SUCCESS) throw std::runtime_error("failed to enumerate variables");

		__debugbreak();

		for (const auto& var : input_vars) {
			auto logger = JELOG_WARN;
			logger << var->name;
		}

		spvReflectDestroyShaderModule(&module);
	}*/

	try {
		GLFW::Init();
		Input::Init();
	} catch (std::exception e) {
		GLFWLOG_CRITICAL << "GLFW ERROR: " << e.what();
		throw e;
	}

	try {
		Vulkan::Instance::Init(appName, appVersion, "Junia", GetEngineVersion());
	} catch (std::exception e) {
		VKLOG_CRITICAL << "Vulkan ERROR: " << e.what();
		throw e;
	}
}

void Terminate() {
	Window::DestroyAll();
	Vulkan::Instance::Terminate();
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
