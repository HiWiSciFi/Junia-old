#ifdef _WIN32
#include <Windows.h>
#endif

#define GLFW_INCLUDE_VULKAN
#include <glfw/glfw3.h>
#include <stdexcept>
#include "../Junia/Core/InternalLoggers.hpp"

namespace GLFW
{
	/*extern std::vector<GLFWmonitor*> monitors;
	extern std::vector<const GLFWvidmode*> monitorVideoModes;*/
	std::vector<GLFWmonitor*> monitors{ };
	std::vector<const GLFWvidmode*> monitorVideoModes{ };

	void Init()
	{
		glfwSetErrorCallback([ ] (const int code, const char* desc)
			{
				GLFWLOG_ERROR << "GLFW Error: (0x" << std::hex << code << ") : " << desc;
			});

		if (!glfwInit()) throw std::runtime_error("failed to initialize glfw");

		int monitorCount;
		GLFWmonitor** glfwMonitors = glfwGetMonitors(&monitorCount);
		monitors.resize(monitorCount);
		monitorVideoModes.resize(monitorCount);
		GLFWLOG_INFO << "Monitors:";
		for (int i = 0; i < monitorCount; i++)
		{
			monitors[i] = glfwMonitors[i];
			monitorVideoModes[i] = glfwGetVideoMode(monitors[i]);
			GLFWLOG_INFO << "  - " << glfwGetMonitorName(monitors[i]) << " |"
				<< " r:" << monitorVideoModes[i]->redBits
				<< " g:" << monitorVideoModes[i]->greenBits
				<< " b:" << monitorVideoModes[i]->blueBits
				<< " | refresh rate: " << monitorVideoModes[i]->refreshRate
				<< " | " << monitorVideoModes[i]->width << "x" << monitorVideoModes[i]->height;
		}

#ifdef _WIN32
		{
			std::vector<DISPLAY_DEVICE> monitors{ };

			UINT32 pathCount, modeCount;
			if (GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &pathCount, &modeCount) != 0) JECORELOG_INFO << "ERROR";
			std::vector<DISPLAYCONFIG_PATH_INFO> paths(pathCount);
			std::vector<DISPLAYCONFIG_MODE_INFO> modes(modeCount);
			QueryDisplayConfig(QDC_ONLY_ACTIVE_PATHS, &pathCount, paths.data(), &modeCount, modes.data(), nullptr);
			paths.resize(pathCount);
			paths.resize(modeCount);

			DWORD monitorId = 0;
			DISPLAY_DEVICE dummyDevice{ };
			dummyDevice.cb = sizeof(DISPLAY_DEVICE);
			while (EnumDisplayDevices(0, monitorId, &dummyDevice, 0) != 0)
			{
				monitors.push_back(dummyDevice);
				monitorId++;
			}

			JECORELOG_INFO << "Win32 Paths";
			for (size_t i = 0; i < paths.size(); i++)
			{
				DISPLAYCONFIG_TARGET_DEVICE_NAME targetName{ };
				targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
				targetName.header.adapterId = paths[i].targetInfo.adapterId;
				targetName.header.id = paths[i].targetInfo.id;
				targetName.header.size = sizeof(DISPLAYCONFIG_TARGET_DEVICE_NAME);
				if (DisplayConfigGetDeviceInfo(&targetName.header) != 0) continue;
				std::wstring wstr(targetName.monitorFriendlyDeviceName);
				std::string str(wstr.begin(), wstr.end());
				JECORELOG_INFO << "  - " << str.c_str();
				std::wstring wstr2(targetName.monitorDevicePath);
				std::string str2(wstr2.begin(), wstr2.end());
				JECORELOG_INFO << "      - " << str2.c_str();

				//JECORELOG_INFO << "";
			}

			JECORELOG_INFO << "Win32 Monitors";
			for (size_t i = 0; i < monitors.size(); i++)
			{
				EnumDisplayDevices(monitors[i].DeviceName, 0, &dummyDevice, EDD_GET_DEVICE_INTERFACE_NAME);
				JECORELOG_INFO << "  - " << dummyDevice.DeviceString;
				JECORELOG_INFO << "      - name: " << monitors[i].DeviceName;
				JECORELOG_INFO << "      - string: " << monitors[i].DeviceString;
				JECORELOG_INFO << "      - ID: " << dummyDevice.DeviceID;

				DISPLAYCONFIG_TARGET_DEVICE_NAME targetName{ };
				targetName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
				targetName.header.adapterId = paths[i].targetInfo.adapterId;
				targetName.header.id = paths[i].targetInfo.id;
				targetName.header.size = sizeof(DISPLAYCONFIG_TARGET_DEVICE_NAME);
				if (DisplayConfigGetDeviceInfo(&targetName.header) != 0) continue;
				std::wstring wstr(targetName.monitorFriendlyDeviceName);
				std::string str(wstr.begin(), wstr.end());
				JECORELOG_INFO << "      - friendly name: " << str.c_str();
			}
		}
#endif
	}
}
