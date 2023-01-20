#include "ExtensionLoader.hpp"
#include <Platform/Vulkan/Exception.hpp>

namespace Vulkan
{
	PFN_vkCreateDebugUtilsMessengerEXT func_vkCreateDebugUtilsMessengerEXT = nullptr;
	PFN_vkDestroyDebugUtilsMessengerEXT func_vkDestroyDebugUtilsMessengerEXT = nullptr;

	extern void* instance;

	template<typename FUNC>
	static FUNC vkLoadFunc(const char* funcname)
	{
		FUNC func = reinterpret_cast<FUNC>(vkGetInstanceProcAddr(reinterpret_cast<VkInstance>(instance), funcname));
		if (func == nullptr) throw Exception("failed to load vulkan function");
		return func;
	}

	void LoadExtensions(bool debug)
	{
		if (debug)
		{
			func_vkCreateDebugUtilsMessengerEXT = vkLoadFunc<PFN_vkCreateDebugUtilsMessengerEXT>("vkCreateDebugUtilsMessengerEXT");
			func_vkDestroyDebugUtilsMessengerEXT = vkLoadFunc<PFN_vkDestroyDebugUtilsMessengerEXT>("vkDestroyDebugUtilsMessengerEXT");
		}
	}
}
