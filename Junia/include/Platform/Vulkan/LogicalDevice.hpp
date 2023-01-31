#pragma once

namespace Vulkan
{
	class LogicalDevice
	{
	private:
		void* logicalDevice = nullptr;

	public:
		LogicalDevice();
		~LogicalDevice();
	};
}
