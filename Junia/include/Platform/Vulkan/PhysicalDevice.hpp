#pragma once

#include <vector>

namespace Vulkan
{
	class PhysicalDevice
	{
	private:
		void* physicalDevice = nullptr;

	public:
		static std::vector<PhysicalDevice> GetDevices();

		PhysicalDevice();
		~PhysicalDevice();

		inline void* Get() { return physicalDevice; }
	};
}
