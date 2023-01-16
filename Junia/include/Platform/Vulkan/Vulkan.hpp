#pragma once

#include <cstdint>
#include <string>

namespace Vulkan
{
	void Init(std::string const& appName, uint32_t appVersion, std::string const& engineName, uint32_t engineVersion, bool debug = false);
}
