#include <GLFW/glfw3.h>
#ifdef _WIN32
#include <Windows.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#endif
#include "GlfwMonitor.hpp"
#include <vector>
#include <sstream>

#include "../../Junia/Core/InternalLoggers.hpp"

namespace GLFW
{
	#ifdef _WIN32
	std::vector<DISPLAY_DEVICE> displayDevices{ };
	std::vector<DISPLAYCONFIG_TARGET_DEVICE_NAME> deviceNameTargets{ };
	#endif

	GlfwMonitor::GlfwMonitor(GLFWmonitor* monitor, size_t index) : monitor(monitor)
	{
		glfwSetMonitorUserPointer(monitor, this);
		videoMode = glfwGetVideoMode(monitor);

		#ifdef _WIN32

		const char* displayName = glfwGetWin32Monitor(monitor);
		std::stringstream nameSs;
		nameSs << index << ": ";

		bool found = false;
		for (size_t i = 0; i < displayDevices.size(); i++)
		{
			if (strcmp(displayDevices[i].DeviceName, displayName) == 0)
			{
				std::wstring wstr(deviceNameTargets[i].monitorFriendlyDeviceName);
				nameSs << std::string(wstr.begin(), wstr.end())
					<< " (" << glfwGetMonitorName(monitor) << ")";
				name = nameSs.str();
				found = true;
				break;
			}
		}

		if (!found)
		#endif
		{
			nameSs << glfwGetMonitorName(monitor);
		}
		name = nameSs.str();
	}

	GlfwMonitor::~GlfwMonitor()
	{

	}

	const std::string& GlfwMonitor::GetName() const
	{
		return name;
	}

	uint32_t GlfwMonitor::GetWidth() const
	{
		return static_cast<uint32_t>(videoMode->width);
	}

	uint32_t GlfwMonitor::GetHeight() const
	{
		return static_cast<uint32_t>(videoMode->height);
	}

	uint32_t GlfwMonitor::GetRedBits() const
	{
		return static_cast<uint8_t>(videoMode->redBits);
	}

	uint32_t GlfwMonitor::GetGreenBits() const
	{
		return static_cast<uint8_t>(videoMode->greenBits);
	}

	uint32_t GlfwMonitor::GetBlueBits() const
	{
		return static_cast<uint8_t>(videoMode->blueBits);
	}

	uint32_t GlfwMonitor::GetRefreshRate() const
	{
		return static_cast<uint32_t>(videoMode->refreshRate);
	}
}
