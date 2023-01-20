#pragma once

#include <Junia/Core/Version.hpp>
#include <Platform/Vulkan/PhysicalDevice.hpp>
#include <cstdint>
#include <string>

namespace Vulkan
{
	extern void* instance;
	extern bool debug;
	extern PhysicalDevice physicalDevice;

	template<typename T> constexpr T GetAs(void* i) { return reinterpret_cast<T>(i); }

	void Init(std::string const& appName, Junia::Version const& appVersion, std::string const& engineName, Junia::Version const& engineVersion, bool debug = false);
	void Cleanup();

	void RequireExtension(std::string const& extension);
	void RequireDeviceExtension(std::string const& extension);

	void PickPhysicalDevice();
}
