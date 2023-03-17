#include <GLFW/glfw3.h>
#if defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN
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
			// TODO: remove, since this is already covered by GLFW
			Display* display = glfwGetX11Display();
			int defaultScreen = reinterpret_cast<_XPrivDisplay>(display)->default_screen;
			Window rootWindow = reinterpret_cast<_XPrivDisplay>(display)->screens[defaultScreen].root;
			XRRScreenResources* screenResources = XRRGetScreenResources(display, rootWindow);

			RROutput mnt = glfwGetX11Monitor(monitor);
			XRROutputInfo* outputInfo = XRRGetOutputInfo(display, screenResources, mnt);
			GLFWLOG_CRITICAL << outputInfo->name;
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

	JMath::uiVec2 GlfwMonitor::GetPosition() const
	{
		int xpos, ypos;
		glfwGetMonitorPos(monitor, &xpos, &ypos);
		return {
			static_cast<uint32_t>(xpos),
			static_cast<uint32_t>(ypos)
		};
	}

	JMath::uiVec2 GlfwMonitor::GetSize() const
	{
		return {
			static_cast<uint32_t>(videoMode->width),
			static_cast<uint32_t>(videoMode->height)
		};
	}

	JMath::uiVec3 GlfwMonitor::GetColorBits() const
	{
		return {
			static_cast<uint32_t>(videoMode->redBits),
			static_cast<uint32_t>(videoMode->greenBits),
			static_cast<uint32_t>(videoMode->blueBits)
		};
	}

	uint32_t GlfwMonitor::GetRefreshRate() const
	{
		return static_cast<uint32_t>(videoMode->refreshRate);
	}

	void* GlfwMonitor::GetNative() const
	{
		return monitor;
	}
}
