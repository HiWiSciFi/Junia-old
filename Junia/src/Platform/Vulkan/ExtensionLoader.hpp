#pragma once

#include <vulkan/vulkan.hpp>
#include <vector>

namespace Junia::Vulkan {

void LoadExtensions(VkInstance instance, std::vector<const char*>& extensions);

} // namespace Junia::Vulkan
