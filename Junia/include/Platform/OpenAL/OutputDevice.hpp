#pragma once

#include <vector>

namespace OpenAL
{
	class OutputDevice
	{
	private:
		static std::vector<OutputDevice> devices;

	public:
		static inline const std::vector<OutputDevice>& GetOutputDevices() { return devices; }

	protected:
		OutputDevice(const char* deviceName);
		virtual ~OutputDevice() = default;
	};
}
