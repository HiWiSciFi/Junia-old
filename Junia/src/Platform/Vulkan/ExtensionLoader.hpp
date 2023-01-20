#include <vulkan/vulkan.h>

namespace Vulkan
{
	void LoadExtensions(bool debug);

	extern PFN_vkCreateDebugUtilsMessengerEXT func_vkCreateDebugUtilsMessengerEXT;
	extern PFN_vkDestroyDebugUtilsMessengerEXT func_vkDestroyDebugUtilsMessengerEXT;

	/**
	 * @brief Create a debug messenger object
	 * @param instance is the instance the messenger will be used with.
	 * @param pCreateInfo is a pointer to a VkDebugUtilsMessengerCreateInfoEXT
	 *                    structure containing the callback pointer, as well as
	 *                    defining conditions under which this messenger will
	 *                    trigger the callback.
	 * @param pAllocator controls host memory allocation.
	 * @param pMessenger is a pointer to a VkDebugUtilsMessengerEXT handle in
	 *                   which the created object is returned.
	 * @return VK_SUCCESS on success and VK_ERROR_OUT_OF_HOST_MEMORY on failure
	*/
	constexpr VkResult vkCreateDebugUtilsMessengerEXT(
		VkInstance instance,
		const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
		const VkAllocationCallbacks* pAllocator,
		VkDebugUtilsMessengerEXT* pMessenger)
	{
		return func_vkCreateDebugUtilsMessengerEXT(instance, pCreateInfo, pAllocator, pMessenger);
	}

	/**
	 * @brief Destroy a debug messenger object
	 * @param instance is the instance where the callback was created.
	 * @param messenger is the VkDebugUtilsMessengerEXT object to destroy.
	 *                  messenger is an externally synchronized object and must
	 *                  not be used on more than one thread at a time. This
	 *                  means that vkDestroyDebugUtilsMessengerEXT must not be
	 *                  called when a callback is active.
	 * @param pAllocator controls host memory allocation.
	*/
	constexpr void vkDestroyDebugUtilsMessengerEXT(
		VkInstance instance,
		VkDebugUtilsMessengerEXT messenger,
		const VkAllocationCallbacks* pAllocator)
	{
		func_vkDestroyDebugUtilsMessengerEXT(instance, messenger, pAllocator);
	}
}
