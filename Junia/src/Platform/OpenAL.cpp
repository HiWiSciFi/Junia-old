#include <Platform/OpenAL.hpp>
#include <al.h>
#include <alc.h>
#include <Platform/OpenAL/Exception.hpp>
#include <vector>
#include <iostream>
#include <Junia/Core/Log.hpp>
#include <cstring>

namespace OpenAL
{
	Junia::Log::Logger alLog = Junia::Log::Logger("OpenAL", &std::cout);

	void alEnumerateOutputDevices(size_t* deviceCount, const char** deviceNames)
	{
		size_t counter = 0;
		const char* devices = alcGetString(nullptr, ALC_ALL_DEVICES_SPECIFIER);
		const char* device = devices;

		for (size_t len; (len = strlen(device)), len != 0; device += len + 1)
		{
			if (deviceNames != nullptr)
			{
				if (len > 20 && strncmp("Generic Software on ", device, 20) == 0)
				{
					device += 20;
					len -= 20;
				}
				deviceNames[counter] = device;
			}
			counter++;
		}
		if (deviceCount != nullptr) (*deviceCount) = counter;
	}

	void alEnumerateInputDevices(size_t* deviceCount, const char** deviceNames)
	{
		size_t counter = 0;
		const char* devices = alcGetString(nullptr, ALC_CAPTURE_DEVICE_SPECIFIER);
		const char* device = devices;

		for (size_t len; (len = strlen(device)), len != 0; device += len + 1)
		{
			if (deviceNames != nullptr)
			{
				deviceNames[counter] = device;
			}
			counter++;
		}
		if (deviceCount != nullptr) (*deviceCount) = counter;
	}

	void Init()
	{
		ALboolean enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATE_ALL_EXT");
		if (enumeration == AL_FALSE) alLog.Trace() << "device enumeration not supported";

		size_t outputDeviceCount;
		alEnumerateOutputDevices(&outputDeviceCount, nullptr);
		std::vector<const char*> outputDevices(outputDeviceCount);
		alEnumerateOutputDevices(&outputDeviceCount, outputDevices.data());
		alLog.Info() << "Available output devices:";
		for (const auto& device : outputDevices) alLog.Info() << "  - " << device;

		size_t inputDeviceCount;
		alEnumerateInputDevices(&inputDeviceCount, nullptr);
		std::vector<const char*> inputDevices(inputDeviceCount);
		alEnumerateInputDevices(&inputDeviceCount, inputDevices.data());
		alLog.Info() << "Available input devices:";
		for (const auto& device : inputDevices) alLog.Info() << "  - " << device;

		ALCdevice* device = alcOpenDevice(nullptr);
		if (device == nullptr)
		{
			std::cout << "Could not open device" << std::endl;
		}
	}
}
