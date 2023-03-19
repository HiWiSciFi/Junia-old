#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_VULKAN
#include "../Junia/Core/InternalLoggers.hpp"
#include "Vulkan.hpp"
#include "Vulkan/VulkanDevice.hpp"
#include "Vulkan/VulkanExtensionLoader.hpp"
#include "../Util/util_cstring.hpp"
#include <stdexcept>

namespace Vulkan
{
	static VkDebugUtilsMessengerEXT debugMessenger = nullptr;

	VkInstance vkInstance = nullptr;
	bool debug = false;
	std::vector<const char*> requiredExtensions{ };
	std::vector<const char*> requiredDeviceExtensions{ };
	std::vector<const char*> enabledValidationLayers{ };
	std::vector<Junia::RenderDevice*> renderDevices;

	extern VulkanDevice* vkDevice;

	VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT severity,
		VkDebugUtilsMessageTypeFlagsEXT types,
		const VkDebugUtilsMessengerCallbackDataEXT* data,
		void* pUserData)
	{
		if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
			VKLOG_ERROR << data->pMessage;
		else if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
			VKLOG_WARN << data->pMessage;
		else if (debug && severity & (VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT))
			VKLOG_TRACE << data->pMessage;
		return VK_FALSE;
	}

	void Init(std::string const& appName, Junia::Version const& appVersion, std::string const& engineName, Junia::Version const& engineVersion, bool debug)
	{
		if (vkInstance != nullptr)
		{
			JECORELOG_WARN << "Vulkan has already been initialized. This call to Vulkan::Init will be ignored.";
			return;
		}

		uint32_t glfwExtensionCount;
		const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		for (uint32_t i = 0; i < glfwExtensionCount; i++) Vulkan::RequireExtension(glfwExtensions[i]);

		Vulkan::debug = debug;
		RequireDeviceExtension(VK_KHR_SWAPCHAIN_EXTENSION_NAME);
		VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo{ };
		if (debug)
		{
			RequireExtension(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
			uint32_t layerCount;
			vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
			std::vector<VkLayerProperties> availableLayers(layerCount);
			vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

			std::vector<const char*> validationLayersToEnable{ "VK_LAYER_KHRONOS_validation" };
			for (const char* layerName : validationLayersToEnable)
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
				if (!found)
				{
					JECORELOG_WARN << "Vulkan validation layer \"" << layerName << "\" not supported on this device. Continuing without it.";
					continue;
				}
				enabledValidationLayers.push_back(layerName);
			}

			debugMessengerCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			debugMessengerCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT;
			debugMessengerCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
			debugMessengerCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
			debugMessengerCreateInfo.messageSeverity |= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			debugMessengerCreateInfo.messageType |= VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
			debugMessengerCreateInfo.messageType |= VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
			debugMessengerCreateInfo.pfnUserCallback = VulkanDebugCallback;
		}

		VkApplicationInfo appInfo{ };
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.apiVersion = VK_API_VERSION_1_3;
		appInfo.pEngineName = engineName.c_str();
		appInfo.engineVersion = engineVersion.GetVersionNumber();
		appInfo.pApplicationName = appName.c_str();
		appInfo.applicationVersion = appVersion.GetVersionNumber();

		VkInstanceCreateInfo instanceCreateInfo{ };
		instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		instanceCreateInfo.pApplicationInfo = &appInfo;
		instanceCreateInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
		instanceCreateInfo.ppEnabledExtensionNames = requiredExtensions.data();
		instanceCreateInfo.enabledLayerCount = debug ? static_cast<uint32_t>(enabledValidationLayers.size()) : 0;
		instanceCreateInfo.ppEnabledLayerNames = debug ? enabledValidationLayers.data() : nullptr;
		instanceCreateInfo.pNext = debug ? &debugMessengerCreateInfo : nullptr;

		if (vkCreateInstance(&instanceCreateInfo, nullptr, &vkInstance) != VK_SUCCESS)
			throw std::runtime_error("failed to create vulkan instance");

		LoadExtensions(requiredExtensions.size(), requiredExtensions.data());

		if (debug && vkCreateDebugUtilsMessengerEXT(vkInstance, &debugMessengerCreateInfo, nullptr, &debugMessenger) != VK_SUCCESS)
			throw std::runtime_error("failed to create vulkan debug messenger");

		uint32_t deviceCount;
		vkEnumeratePhysicalDevices(vkInstance, &deviceCount, nullptr);
		if (deviceCount == 0) throw std::runtime_error("failed to find any suitable vulkan render devices");
		std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
		vkEnumeratePhysicalDevices(vkInstance, &deviceCount, physicalDevices.data());
		for (const auto& physicalDevice : physicalDevices)
		{
			Junia::RenderDevice* device = new VulkanDevice(physicalDevice);
			if (device->GetRating() != 0) renderDevices.push_back(device);
		}
	}

	void RequireExtension(std::string const& extension)
	{
		if (vkInstance != nullptr)
			throw std::runtime_error("cannot require extension after initialization");

		for (auto const& e : requiredExtensions) if (strcmp(e, extension.c_str()) == 0) return;
		size_t length = strlen(extension.c_str()) + 1;
		char* str = new char[length];
		if (util_strcpy_s(str, length, extension.c_str()) != 0)
		{
			VKLOG_ERROR << "Failed to copy required extension name. Continuing without.";
			return;
		}
		VKLOG_INFO << "Required Extension: " << str;
		requiredExtensions.push_back(str);
	}

	void RequireDeviceExtension(std::string const& extension)
	{
		if (vkDevice != nullptr)
			throw std::runtime_error("cannot require device extension after device initialization");

		for (auto const& e : requiredDeviceExtensions) if (strcmp(e, extension.c_str()) == 0) return;
		size_t length = strlen(extension.c_str()) + 1;
		char* str = new char[length];
		if (util_strcpy_s(str, length, extension.c_str()) != 0)
		{
			VKLOG_ERROR << "Failed to copy required extension name. Continuing without.";
			return;
		}
		VKLOG_INFO << "Required Device Extension: " << str;
		requiredDeviceExtensions.push_back(str);
	}

	const std::vector<Junia::RenderDevice*>& GetDevices()
	{
		return renderDevices;
	}

	void PickDevice(Junia::RenderDevice* device)
	{
		if (device == nullptr)
		{
			uint32_t currRating = 0;
			for (size_t i = 0; i < renderDevices.size(); i++)
			{
				if (renderDevices[i]->GetRating() > currRating)
				{
					device = renderDevices[i];
					currRating = device->GetRating();
				}
			}
			if (device == nullptr) throw std::runtime_error("failed to find a suitable device");
			device->Pick();
			return;
		}

		if (device->GetRating() == 0) throw std::runtime_error("device not suitable");
		for (size_t i = 0; i < renderDevices.size(); i++)
			if (renderDevices[i] == device) { device->Pick(); return; }
		throw std::runtime_error("device not in list of available devices");
	}

	void Cleanup()
	{
		for (auto renderDevice : renderDevices) delete renderDevice;
		if (debug) vkDestroyDebugUtilsMessengerEXT(vkInstance, debugMessenger, nullptr);
		vkDestroyInstance(vkInstance, nullptr);
	}
}
