#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Platform/Vulkan.hpp>
#include <Platform/Vulkan/Exception.hpp>
#include <vector>
#include <Junia/Core/Log.hpp>
#include <iostream>
#include <cstring>

#include "Vulkan/ExtensionLoader.hpp"

namespace Vulkan
{
	Junia::Log::Logger vkLog = Junia::Log::Logger("Vulkan", &std::cout);

	void* instance = nullptr;
	void* device = nullptr;
	bool debug = false;
	PhysicalDevice physicalDevice;

	static std::vector<const char*> requiredExtensions{ };
	static std::vector<const char*> requiredDeviceExtensions{ };

	static VkDebugUtilsMessengerEXT debugMessenger = nullptr;

	const std::vector<const char*> VALIDATION_LAYERS{ "VK_LAYER_KHRONOS_validation" };

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT severity,
		VkDebugUtilsMessageTypeFlagsEXT types,
		const VkDebugUtilsMessengerCallbackDataEXT* data,
		void* pUserData)
	{
		if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
			vkLog.Error() << data->pMessage;
		else if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
			vkLog.Warn() << data->pMessage;
		else if (severity & (VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT))
			vkLog.Trace() << data->pMessage;
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
	}

	void Init(std::string const& appName, Junia::Version const& appVersion, std::string const& engineName, Junia::Version const& engineVersion, bool debug)
	{
		if (instance != nullptr) throw Exception("vulkan has already been initialized");

		Vulkan::debug = debug;

		// For MacOS (currently not supported)
		//RequireExtension(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

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
				for (const auto& layerProperties : availableLayers)
				{
					if (strcmp(layerName, layerProperties.layerName) == 0)
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

		// log available extensions
		/*uint32_t extensionCount;
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> extensions(extensionCount);
		vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());
		vkLog.Warn() << "Available instance extensions:";
		for (const auto& extension : extensions) vkLog.Warn() << "  - " << extension.extensionName;*/

		VkInstanceCreateInfo instanceCreateInfo{ };
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pApplicationInfo = &appInfo;
		// For MacOS (currently not supported)
		//instanceCreateInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
		instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
		instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();
		instanceCreateInfo.enabledLayerCount = debug ? static_cast<uint32_t>(VALIDATION_LAYERS.size()) : 0;
		instanceCreateInfo.ppEnabledLayerNames = debug ? VALIDATION_LAYERS.data() : nullptr;
		instanceCreateInfo.pNext = debug ? &debugMessengerCreateInfo : nullptr;

		if (vkCreateInstance(&instanceCreateInfo, nullptr, GetAs<VkInstance*>(&instance)) != VK_SUCCESS)
			throw Exception("vulkan instance could not be created");

		LoadExtensions(debug);

		if (debug)
		{
			if (Vulkan::vkCreateDebugUtilsMessengerEXT(GetAs<VkInstance>(instance), &debugMessengerCreateInfo, nullptr, &debugMessenger) != VK_SUCCESS)
				throw Exception("vulkan debug messenger could not be created");
		}
	}

	void PickPhysicalDevice()
	{
		uint32_t deviceCount;
		vkEnumeratePhysicalDevices(GetAs<VkInstance>(instance), &deviceCount, nullptr);
		if (deviceCount == 0)
		{
			const char* errStr = "could not find gpu with vulkan support";
			vkLog.Critical() << errStr;
			throw Exception(errStr);
		}
		std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
		vkEnumeratePhysicalDevices(GetAs<VkInstance>(instance), &deviceCount, physicalDevices.data());

		vkLog.Info() << "PhysicalDevice count: " << deviceCount;
		for (const auto& device : physicalDevices)
		{
			VkPhysicalDeviceProperties properties{ };
			vkGetPhysicalDeviceProperties(device, &properties);
			vkLog.Info() << "  - " << properties.deviceName;
		}
	}

	void RequireExtension(std::string const& extension)
	{
		if (instance != nullptr) throw Exception("cannot require extension after initialization");

		for (auto const& e : requiredExtensions)
		{
			if (strcmp(e, extension.c_str()) == 0) throw Exception("extension has already been registered");
		}
		size_t length = strlen(extension.c_str());
		char* str = new char[length+1];
		strncpy(str, extension.c_str(), length);
		str[length] = '\0';
		vkLog.Info() << "Required Extension: " << str;
		requiredExtensions.push_back(str);
	}

	void RequireDeviceExtension(std::string const& extension)
	{
		if (physicalDevice.Get() != nullptr) throw Exception("cannot require device extension after device initialization");

		for (auto const& e : requiredDeviceExtensions)
		{
			if (strcmp(e, extension.c_str()) == 0) throw Exception("device extension has already been registered");
		}
		size_t length = strlen(extension.c_str());
		char* str = new char[length + 1];
		strncpy(str, extension.c_str(), length);
		str[length] = '\0';
		vkLog.Info() << "Required Device Extension: " << str;
		requiredDeviceExtensions.push_back(str);
	}

	void Cleanup()
	{
		if (debug) Vulkan::vkDestroyDebugUtilsMessengerEXT(GetAs<VkInstance>(instance), debugMessenger, nullptr);
		vkDestroyInstance(GetAs<VkInstance>(instance), nullptr);
	}
}
