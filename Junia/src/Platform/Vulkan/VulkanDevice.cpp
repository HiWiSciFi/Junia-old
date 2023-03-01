#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include "VulkanDevice.hpp"
#include <stdexcept>
#include <vector>
#include <set>
#include <string>

namespace Vulkan
{
	extern VkInstance vkInstance;
	extern bool debug;
	extern std::vector<const char*> requiredDeviceExtensions;
	VulkanDevice* vkDevice = nullptr;

	extern std::vector<const char*> VALIDATION_LAYERS;

	VulkanDevice::VulkanDevice(VkPhysicalDevice phDevice)
	{
		physicalDevice = phDevice;

		vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);
		if (!deviceFeatures.geometryShader) { rating = 0; return; }
		vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);
		switch (deviceProperties.deviceType)
		{
		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   type = Junia::RenderDeviceType::DISCRETE_GPU;   break;
		case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    type = Junia::RenderDeviceType::VIRTUAL_GPU;    break;
		case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: type = Junia::RenderDeviceType::INTEGRATED_GPU; break;
		case VK_PHYSICAL_DEVICE_TYPE_CPU:            type = Junia::RenderDeviceType::CPU;            break;
		case VK_PHYSICAL_DEVICE_TYPE_OTHER: default: type = Junia::RenderDeviceType::OTHER;          break;
		}
		rating = (static_cast<uint32_t>(type) * 1000) + 1;
		rating += deviceProperties.limits.maxImageDimension2D;

		// device extension support
		uint32_t extensionCount;
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);
		std::vector<VkExtensionProperties> availableExtensions(extensionCount);
		vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());
		rating += extensionCount;
		std::set<std::string> requiredExtensions(requiredDeviceExtensions.begin(), requiredDeviceExtensions.end());
		for (const auto& extension : availableExtensions) requiredExtensions.erase(extension.extensionName);
		if (!requiredExtensions.empty()) { rating = 0; return; }

		// find queue families
		uint32_t queueFamilyCount;
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
		std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
		vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());

		// dummy surface creation
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
		GLFWwindow* dummyWindow = glfwCreateWindow(1, 1, "dummy window", nullptr, nullptr);
		if (dummyWindow == nullptr) throw std::runtime_error("failed to create dummy window");

		VkSurfaceKHR dummySurface = nullptr;
		bool failed = false;
		if (glfwCreateWindowSurface(vkInstance, dummyWindow, nullptr, &dummySurface) == VK_SUCCESS)
		{
			// check queue families
			for (uint32_t i = 0; i < queueFamilyCount; i++)
			{
				if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) graphicsQueueIndex = i;
				if (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT) computeQueueIndex = i;
				VkBool32 presentSupport = false;
				vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, dummySurface, &presentSupport);
				if (presentSupport) presentQueueIndex = i;
			}

			uint32_t formatCount;
			vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, dummySurface, &formatCount, nullptr);
			if (formatCount == 0) failed = true;

			uint32_t presentModeCount;
			vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, dummySurface, &presentModeCount, nullptr);
			if (presentModeCount == 0) failed = true;

			// dummy surface destruction
			vkDestroySurfaceKHR(vkInstance, dummySurface, nullptr);
		} else throw std::runtime_error("failed to create dummy surface");

		glfwDestroyWindow(dummyWindow);
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		if (failed ||
			!graphicsQueueIndex.has_value() ||
			!presentQueueIndex.has_value() ||
			!computeQueueIndex.has_value())
		{
			rating = 0;
			return;
		}

		if (graphicsQueueIndex.value() == presentQueueIndex.value()) rating += 100;
	}

	VulkanDevice::~VulkanDevice()
	{
		if (logicalDevice != nullptr)
			vkDestroyDevice(logicalDevice, nullptr);
	}

	void VulkanDevice::Pick()
	{
		if (rating == 0) throw std::runtime_error("selected render device is not suitable");

		vkDevice = this;

		// create logical device
		std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{ };
		std::set<uint32_t> uniqueQueueFamilies = {
			graphicsQueueIndex.value(),
			presentQueueIndex.value(),
			computeQueueIndex.value()
		};

		float queuePriorities[] = { 1.0f };
		for (uint32_t queueFamily : uniqueQueueFamilies)
		{
			VkDeviceQueueCreateInfo queueCreateInfo{ };
			queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
			queueCreateInfo.queueFamilyIndex = queueFamily;
			queueCreateInfo.queueCount = 1;
			queueCreateInfo.pQueuePriorities = queuePriorities;
			queueCreateInfos.push_back(queueCreateInfo);
		}

		VkPhysicalDeviceFeatures requiredDeviceFeatures{ };
		requiredDeviceFeatures.geometryShader = true;

		VkDeviceCreateInfo createInfo{ };
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
		createInfo.pQueueCreateInfos = queueCreateInfos.data();
		createInfo.pEnabledFeatures = &requiredDeviceFeatures;
		createInfo.enabledExtensionCount = static_cast<uint32_t>(requiredDeviceExtensions.size());
		createInfo.ppEnabledExtensionNames = requiredDeviceExtensions.data();
		createInfo.enabledLayerCount = debug ? static_cast<uint32_t>(VALIDATION_LAYERS.size()) : 0;
		createInfo.ppEnabledLayerNames = debug ? VALIDATION_LAYERS.data() : nullptr;

		if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &logicalDevice) != VK_SUCCESS)
			throw std::runtime_error("failed to create logical device");

		vkGetDeviceQueue(logicalDevice, graphicsQueueIndex.value(), 0, &graphicsQueue);
		vkGetDeviceQueue(logicalDevice,  presentQueueIndex.value(), 0, &presentQueue );
		vkGetDeviceQueue(logicalDevice,  computeQueueIndex.value(), 0, &computeQueue );
	}
}
