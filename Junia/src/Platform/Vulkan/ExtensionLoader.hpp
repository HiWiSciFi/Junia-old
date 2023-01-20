#include <vulkan/vulkan.h>

namespace Vulkan
{
	void LoadExtensions(bool debug);

	extern PFN_vkCreateDebugUtilsMessengerEXT func_vkCreateDebugUtilsMessengerEXT;
	constexpr VkResult vkCreateDebugUtilsMessengerEXT(
		VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pMessenger)
	{
		return func_vkCreateDebugUtilsMessengerEXT(instance, pCreateInfo, pAllocator, pMessenger);
	}

	extern PFN_vkDestroyDebugUtilsMessengerEXT func_vkDestroyDebugUtilsMessengerEXT;
	constexpr void vkDestroyDebugUtilsMessengerEXT(
		VkInstance instance,
		VkDebugUtilsMessengerEXT messenger,
		const VkAllocationCallbacks* pAllocator)
	{
		func_vkDestroyDebugUtilsMessengerEXT(instance, messenger, pAllocator);
	}
}
