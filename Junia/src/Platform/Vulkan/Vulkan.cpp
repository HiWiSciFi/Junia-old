#include <Platform/Vulkan/Vulkan.hpp>
#include <vulkan/vulkan.h>
#include <vector>
#include <stdexcept>

namespace Vulkan
{
	VkInstance instance = nullptr;
	bool debug = false;

	const std::vector<const char*> VALIDATION_LAYERS{ "VK_LAYER_KHRONOS_validation" };

	void Init(std::string const& appName, uint32_t appVersion, std::string const& engineName, uint32_t engineVersion, bool debug)
	{
		Vulkan::debug = debug;

		if (debug)
		{
			uint32_t layerCount;
			vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
			std::vector<VkLayerProperties> availableLayers(layerCount);
			vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

			for (const char* layerName : VALIDATION_LAYERS)
			{
				bool found = false;
				for (const auto& [name, specVersion, implementationVersion, description] : availableLayers)
				{
					if (strcmp(layerName, name) == 0)
					{
						found = true;
						break;
					}
				}
				if (!found) throw std::runtime_error("no validation layer support");
			}
		}
	}
}
