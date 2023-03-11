#include <GLFW/glfw3.h>
#if defined(_WIN32)
	#include <Windows.h>
	#define GLFW_EXPOSE_NATIVE_WIN32
#elif defined(__linux__)
	#include <X11/Xlib.h>
	#include <X11/extensions/Xrandr.h>
	#undef None
	#define GLFW_EXPOSE_NATIVE_X11
#endif
#define GLFW_NATIVE_INCLUDE_NONE
#include <GLFW/glfw3native.h>
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

		std::stringstream nameSs;
		nameSs << index << ": ";
		bool edidNameFound = false;

#if defined(_WIN32)
		{
			const char* displayName = glfwGetWin32Monitor(monitor);
			for (size_t i = 0; i < displayDevices.size(); i++)
			{
				if (strcmp(displayDevices[i].DeviceName, displayName) == 0)
				{
					std::wstring wstr(deviceNameTargets[i].monitorFriendlyDeviceName);
					nameSs << std::string(wstr.begin(), wstr.end())
						<< " (" << glfwGetMonitorName(monitor) << ")";
					name = nameSs.str();
					edidNameFound = true;
					break;
				}
			}
		}
#elif defined(__linux__)
		{
			Display* display = glfwGetX11Display();
			int screen = ((_XPrivDisplay)(display))->default_screen;
			Window rootWindow = ((&((_XPrivDisplay)(display))->screens[screen])->root);

			//RRCrtc adapt = glfwGetX11Adapter(monitor);
			RROutput mnt = glfwGetX11Monitor(monitor);

			XRRScreenResources* resources = XRRGetScreenResources(display, rootWindow);
			XRROutputInfo* outInfo = XRRGetOutputInfo(display, resources, mnt);
			GLFWLOG_CRITICAL << outInfo->name;
		}
#endif

		if (!edidNameFound)
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
