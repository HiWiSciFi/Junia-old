#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#endif

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_VULKAN
#include <stdexcept>
#include "../Junia/Core/InternalLoggers.hpp"
#include "GLFW/GlfwMonitor.hpp"

namespace Junia
{
	extern std::vector<Monitor*> monitors;
}

namespace GLFW
{
#ifdef _WIN32
	namespace Platform
	{
		namespace Windows
		{
			extern std::vector<DISPLAY_DEVICE> displayDevices;
			extern std::vector<DISPLAYCONFIG_TARGET_DEVICE_NAME> deviceNameTargets;
		}
	}
#endif

	void Init()
	{
		glfwSetErrorCallback([ ] (const int code, const char* desc)
			{
				GLFWLOG_ERROR << "GLFW Error: (0x" << std::hex << code << ") : " << desc;
			});

		if (!glfwInit()) throw std::runtime_error("failed to initialize glfw");

#ifdef _WIN32
		{
			UINT32 pathCount, modeCount;
			if (GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &pathCount, &modeCount) != ERROR_SUCCESS)
				throw std::runtime_error("failed to get display config buffer sizes");
			std::vector<DISPLAYCONFIG_PATH_INFO> displayPaths(pathCount);
			std::vector<DISPLAYCONFIG_MODE_INFO> displayModes(modeCount);
			QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &pathCount, displayPaths.data(), &modeCount, displayModes.data(), nullptr);
			displayPaths.resize(pathCount);
			displayModes.resize(modeCount);
			Platform::Windows::displayDevices.resize(pathCount);
			Platform::Windows::deviceNameTargets.resize(pathCount);

			for (size_t i = 0; i < displayPaths.size(); i++)
			{
				DISPLAYCONFIG_TARGET_DEVICE_NAME nameTarget{ };
				nameTarget.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
				nameTarget.header.size = sizeof(DISPLAYCONFIG_TARGET_DEVICE_NAME);
				nameTarget.header.adapterId = displayPaths[i].targetInfo.adapterId;
				nameTarget.header.id = displayPaths[i].targetInfo.id;
				if (DisplayConfigGetDeviceInfo(&nameTarget.header) == ERROR_SUCCESS)
					Platform::Windows::deviceNameTargets[i] = nameTarget;
			}

			DISPLAY_DEVICE d1{ };
			d1.cb = sizeof(DISPLAY_DEVICE);
			for (DWORD monitorId = 0; EnumDisplayDevices(0, monitorId, &d1, 0); monitorId++)
			{
				DISPLAY_DEVICE d2{ };
				d2.cb = sizeof(DISPLAY_DEVICE);
				EnumDisplayDevices(d1.DeviceName, 0, &d2, EDD_GET_DEVICE_INTERFACE_NAME);
				for (size_t i = 0; i < displayPaths.size(); i++)
				{
					std::wstring wstr(Platform::Windows::deviceNameTargets[i].monitorDevicePath);
					std::string monitorPath(wstr.begin(), wstr.end());

					if (monitorPath == d2.DeviceID)
					{
						Platform::Windows::displayDevices[i] = d2;
						break;
					}
				}
			}
		}
#endif

		int monitorCount;
		GLFWmonitor** glfwMonitors = glfwGetMonitors(&monitorCount);
		Junia::monitors.resize(monitorCount);
		GLFWLOG_INFO << "Monitors:";
		for (int i = 0; i < monitorCount; i++)
		{
			Junia::Monitor* monitor = new GlfwMonitor(glfwMonitors[i], i);
			Junia::monitors[i] = monitor;
			JMath::uiVec3 colors = monitor->GetColorBits();
			JMath::uiVec2 size = monitor->GetResolution();
			GLFWLOG_INFO << "  - " << monitor->GetName() << " |"
				<< " r:" << colors.r
				<< " g:" << colors.g
				<< " b:" << colors.b
				<< " | refresh rate: " << monitor->GetRefreshRate()
				<< " | " << size.x << "x" << size.y;
		}
	}

	void Cleanup()
	{
		glfwTerminate();
	}
}
