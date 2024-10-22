#include <GLFW/glfw3.h>
#undef APIENTRY

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef ERROR
#undef IGNORE

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_NATIVE_INCLUDE_NONE
#include <GLFW/glfw3native.h>
#undef GLFW_NATIVE_INCLUDE_NONE
#undef GLFW_EXPOSE_NATIVE_WIN32

#endif

#include "GlfwMonitor.hpp"

#include <algorithm>
#include <vector>
#include <sstream>

#include "../../Junia/Core/InternalLoggers.hpp"

namespace GLFW {

#ifdef _WIN32
namespace Platform::Windows {

std::vector<DISPLAY_DEVICE> displayDevices{ };
std::vector<DISPLAYCONFIG_TARGET_DEVICE_NAME> deviceNameTargets{ };

} // namespace Platform::Windows
#endif

GlfwMonitor::GlfwMonitor(GLFWmonitor* monitor, std::size_t index) : monitor(monitor) {
	glfwSetMonitorUserPointer(monitor, this);
	videoMode = glfwGetVideoMode(monitor);

	std::stringstream nameSs;
	nameSs << index << ": ";
	bool edidNameFound = false;

#if defined(_WIN32)
	{
		const char* displayName = glfwGetWin32Monitor(monitor);
		for (std::size_t i = 0; i < Platform::Windows::displayDevices.size(); i++) {
			if (strcmp(Platform::Windows::displayDevices[i].DeviceName, displayName) == 0) {
				std::wstring wstr(Platform::Windows::deviceNameTargets[i].monitorFriendlyDeviceName);
				std::string str(wstr.length(), 0);
				std::transform(wstr.begin(), wstr.end(), str.begin(), [ ] (wchar_t c) { return static_cast<char>(c); });
				nameSs << str.c_str() << " (" << glfwGetMonitorName(monitor) << ")";
				name = nameSs.str();
				edidNameFound = true;
				break;
			}
		}
	}
#endif

	if (!edidNameFound) nameSs << glfwGetMonitorName(monitor);
	name = nameSs.str();
}

GlfwMonitor::~GlfwMonitor() {

}

const std::string& GlfwMonitor::GetName() const {
	return name;
}

JMath::Vec2ui GlfwMonitor::GetPosition() const {
	int xpos, ypos;
	glfwGetMonitorPos(monitor, &xpos, &ypos);
	return {
		static_cast<std::uint32_t>(xpos),
		static_cast<std::uint32_t>(ypos)
	};
}

JMath::Vec2ui GlfwMonitor::GetResolution() const {
	return {
		static_cast<std::uint32_t>(videoMode->width),
		static_cast<std::uint32_t>(videoMode->height)
	};
}

JMath::Vec3ui GlfwMonitor::GetColorBits() const {
	return {
		static_cast<std::uint32_t>(videoMode->redBits),
		static_cast<std::uint32_t>(videoMode->greenBits),
		static_cast<std::uint32_t>(videoMode->blueBits)
	};
}

std::uint32_t GlfwMonitor::GetRefreshRate() const {
	return static_cast<std::uint32_t>(videoMode->refreshRate);
}

void* GlfwMonitor::GetNative() const {
	return monitor;
}

} // namespace GLFW
