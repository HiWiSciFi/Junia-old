#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Platform/Vulkan.hpp>
#include <Platform/Vulkan/Exception.hpp>
#include <vector>
#include <Junia/Core/Log.hpp>
#include <iostream>

namespace Vulkan
{
	void* instance = nullptr;
	void* physicalDevice = nullptr;
	void* device = nullptr;
	bool debug = false;

	static std::vector<const char*> requiredExtensions{ };
	static std::vector<const char*> requiredDeviceExtensions{ };

	static VkDebugUtilsMessengerEXT debugMessenger = nullptr;

	PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT = nullptr;
	PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT = nullptr;

	const std::vector<const char*> VALIDATION_LAYERS{ "VK_LAYER_KHRONOS_validation" };

	template<typename FUNC>
	static FUNC vkLoadFunc(const char* funcname)
	{
		FUNC func = reinterpret_cast<FUNC>(vkGetInstanceProcAddr(GetVkInstance(instance), funcname));
		if (func == nullptr) throw Exception("failed to load vulkan function");
		return func;
	}

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT severity,
		VkDebugUtilsMessageTypeFlagsEXT types,
		const VkDebugUtilsMessengerCallbackDataEXT* data,
		void* pUserData)
	{
		static Junia::Log::Logger vulkanLogger = Junia::Log::Logger("Vulkan", &std::cout);
		if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
			vulkanLogger.Error() << data->pMessage;
		else if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
			vulkanLogger.Warn() << data->pMessage;
		else if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
			vulkanLogger.Info() << data->pMessage;
		else if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
			vulkanLogger.Trace() << data->pMessage;
		return VK_FALSE;
	}

	static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT* createInfo)
	{
		createInfo->sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
		createInfo->messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
		createInfo->messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
		createInfo->messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
		createInfo->messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
		createInfo->messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT;
		createInfo->messageType |= VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
		createInfo->messageType |= VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
		createInfo->pfnUserCallback = VulkanDebugCallback;
		createInfo->pUserData = nullptr;
	}

	void Init(std::string const& appName, Junia::Version const& appVersion, std::string const& engineName, Junia::Version const& engineVersion, bool debug)
	{
		if (instance != nullptr) throw Exception("vulkan has already been initialized");

		Vulkan::debug = debug;

		if (debug) RequireExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
		RequireDeviceExtension(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

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
				if (!found) throw Exception("validation layers not supported");
			}
		}

		VkApplicationInfo appInfo{ };
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.apiVersion = VK_API_VERSION_1_3;
		appInfo.pEngineName = engineName.c_str();
		appInfo.engineVersion = engineVersion.GetVersionNumber();
		appInfo.applicationVersion = appVersion.GetVersionNumber();
		appInfo.pApplicationName = appName.c_str();

		VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo{ };
		if (debug) PopulateDebugMessengerCreateInfo(&debugMessengerCreateInfo);

		VkInstanceCreateInfo instanceCreateInfo{ };
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pApplicationInfo = &appInfo;
		instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
		instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();
		instanceCreateInfo.enabledLayerCount = debug ? static_cast<uint32_t>(VALIDATION_LAYERS.size()) : 0;
		instanceCreateInfo.ppEnabledLayerNames = debug ? VALIDATION_LAYERS.data() : nullptr;
		instanceCreateInfo.pNext = debug ? &debugMessengerCreateInfo : nullptr;

		if (vkCreateInstance(&instanceCreateInfo, nullptr, reinterpret_cast<VkInstance*>(&instance)) != VK_SUCCESS)
			throw Exception("vulkan instance could not be created");

		if (debug)
		{
			vkCreateDebugUtilsMessengerEXT = vkLoadFunc<PFN_vkCreateDebugUtilsMessengerEXT>("vkCreateDebugUtilsMessengerEXT");
			vkDestroyDebugUtilsMessengerEXT = vkLoadFunc<PFN_vkDestroyDebugUtilsMessengerEXT>("vkDestroyDebugUtilsMessengerEXT");

			if (vkCreateDebugUtilsMessengerEXT(GetVkInstance(instance), &debugMessengerCreateInfo, nullptr, &debugMessenger) != VK_SUCCESS)
				throw Exception("vulkan debug messenger could not be created");
		}
	}

	void Cleanup()
	{
		if (debug) vkDestroyDebugUtilsMessengerEXT(GetVkInstance(instance), debugMessenger, nullptr);
		vkDestroyInstance(GetVkInstance(instance), nullptr);
	}

	void RequireExtension(std::string const& extension)
	{
		if (instance != nullptr) throw Exception("cannot require extension after initialization");

		for (auto const& e : requiredExtensions)
		{
			if (strcmp(e, extension.c_str()) == 0) throw Exception("extension has already been registered");
		}
		int length = strlen(extension.c_str());
		char* str = new char[length+1];
		std::strncpy(str, extension.c_str(), length);
		str[length] = '\0';
		requiredExtensions.push_back(str);
	}

	void RequireDeviceExtension(std::string const& extension)
	{
		if (physicalDevice != nullptr) throw Exception("cannot require device extension after device initialization");

		for (auto const& e : requiredDeviceExtensions)
		{
			if (strcmp(e, extension.c_str()) == 0) throw Exception("device extension has already been registered");
		}
		int length = strlen(extension.c_str());
		char* str = new char[length + 1];
		std::strncpy(str, extension.c_str(), length);
		str[length] = '\0';
		requiredDeviceExtensions.push_back(str);
	}
}
