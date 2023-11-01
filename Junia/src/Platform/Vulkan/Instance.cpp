#include "Instance.hpp"

#include <GLFW/glfw3.h>

#include "ExtensionLoader.hpp"
#include "../../Junia/Core/InternalLoggers.hpp"
#include "RenderDevice.hpp"

namespace Junia::Vulkan {

#ifdef NDEBUG
static constexpr bool c_debug = false;
#else
static constexpr bool c_debug = true;
#endif

std::unique_ptr<Vulkan::Instance> Vulkan::Instance::s_instance = nullptr;
std::vector<std::shared_ptr<Vulkan::RenderDevice>> Vulkan::Instance::s_renderDevices { };
std::shared_ptr<Vulkan::RenderDevice> Vulkan::Instance::s_device;

/**
 * @brief Debug callback for Vulkan Debug messages
*/
static VKAPI_ATTR VkBool32 VKAPI_CALL VulkanDebugCallback(
	VkDebugUtilsMessageSeverityFlagBitsEXT      severity,
	VkDebugUtilsMessageTypeFlagsEXT             types,
	const VkDebugUtilsMessengerCallbackDataEXT* data,
	void*                                       pUserData)
{
	if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
		VKLOG_ERROR << data->pMessage;
	else if (severity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		VKLOG_ERROR << data->pMessage;
	else if constexpr (c_debug) {
		if (severity & (VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT))
			VKLOG_TRACE << data->pMessage;
	}
	return VK_FALSE;
}

Vulkan::Instance::Instance(const std::string& appName, Junia::Version appVersion, const std::string& engineName, Junia::Version engineVersion)
	: debugMessenger(VK_NULL_HANDLE) {
	// Fill out Application Info
	VkApplicationInfo appInfo{
		.sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO,
		.pApplicationName   = appName.c_str(),
		.applicationVersion = appVersion.GetVersionNumber(),
		.pEngineName        = engineName.c_str(),
		.engineVersion      = engineVersion.GetVersionNumber(),
		.apiVersion         = VK_API_VERSION_1_3
	};

	// Get Required GLFW Instance extensions
	std::uint32_t glfwExtensionCount;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	// Add GLFW Extensions to instance Extensions
	std::vector<const char*> instanceExtensions(glfwExtensionCount + c_debug);
	memcpy(instanceExtensions.data(), glfwExtensions, glfwExtensionCount * sizeof(const char*));

	// Select vulkan layers to enable
	std::vector<const char*> layersToEnable(c_debug);
	std::vector<const char*> enabledLayers{ };
	enabledLayers.reserve(layersToEnable.size());
	uint32_t availableLayerCount;
	vkEnumerateInstanceLayerProperties(&availableLayerCount, nullptr);
	std::vector<VkLayerProperties> availableLayers(availableLayerCount);
	vkEnumerateInstanceLayerProperties(&availableLayerCount, availableLayers.data());
	VkDebugUtilsMessengerCreateInfoEXT debugMessengerCreateInfo;
	
	if constexpr (c_debug) {
		// Add vulkan debug extensions and layer
		instanceExtensions.back() = VK_EXT_DEBUG_UTILS_EXTENSION_NAME;
		layersToEnable.front() = "VK_LAYER_KHRONOS_validation";

		// check if layers are available
		for (const char* layerName : layersToEnable) {
			bool found = false;
			for (const auto& layerProperties : availableLayers) {
				found = strcmp(layerName, layerProperties.layerName) == 0;
				if (found) break;
			}
			if (!found) VKLOG_WARN << "Vulkan layer \"" << layerName << "\" not available on this machine. Continuing without it.";
			else enabledLayers.push_back(layerName);
		}

		// Create debug messenger
		debugMessengerCreateInfo = {
			.sType           = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
			.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
			                    | VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
			                    | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
			                    | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
			.messageType     = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
			                    | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
			.pfnUserCallback = VulkanDebugCallback
		};
	}

	// Fill out Instance Info
	VkInstanceCreateInfo instanceCreateInfo{
		.sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
		.pNext                   = c_debug ? &debugMessengerCreateInfo : nullptr,
		.pApplicationInfo        = &appInfo,
		.enabledLayerCount       = static_cast<std::uint32_t>(enabledLayers.size()),
		.ppEnabledLayerNames     = enabledLayers.data(),
		.enabledExtensionCount   = static_cast<std::uint32_t>(instanceExtensions.size()),
		.ppEnabledExtensionNames = instanceExtensions.data(),
	};

	// Create instance
	if (vkCreateInstance(&instanceCreateInfo, nullptr, &this->instance) != VK_SUCCESS)
		throw std::runtime_error("failed to create vulkan instance");

	// Load function pointers for vulkan extensions
	Vulkan::LoadExtensions(this->instance, instanceExtensions);

	// Create Debug Messenger
	if constexpr (c_debug) {
		if (vkCreateDebugUtilsMessengerEXT(this->instance, &debugMessengerCreateInfo, nullptr, &this->debugMessenger) != VK_SUCCESS)
			VKLOG_WARN << "Failed to create Vulkan debug messenger. Continuing without it.";
	}
}

Vulkan::Instance::~Instance() {
	s_renderDevices.clear();
	s_device.reset();
	if constexpr (c_debug) vkDestroyDebugUtilsMessengerEXT(this->instance, debugMessenger, nullptr);
	if (this->instance != VK_NULL_HANDLE) vkDestroyInstance(this->instance, nullptr);
}

void Vulkan::Instance::EnumerateDevices() {
	std::vector<std::shared_ptr<Vulkan::RenderDevice>> availableRenderDevices{ };

	// Get vulkan physical devices
	std::uint32_t physicalDeviceCount;
	vkEnumeratePhysicalDevices(Vulkan::Instance::Get(), &physicalDeviceCount, nullptr);
	std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
	vkEnumeratePhysicalDevices(Vulkan::Instance::Get(), &physicalDeviceCount, physicalDevices.data());

	// Create dummy window for device creation
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
	GLFWwindow* dummyWindow = glfwCreateWindow(1, 1, "", nullptr, nullptr);
	if (dummyWindow == nullptr) throw std::runtime_error("failed to create window for rendering device rating");

	// Create Vulkan::RenderDevice for each physical device
	std::uint32_t eligibleDeviceCount = 0;
	for (const auto& physicalDevice : physicalDevices) {
		availableRenderDevices.emplace_back(std::make_shared<Vulkan::RenderDevice>(physicalDevice, dummyWindow));
		if (availableRenderDevices.back()->GetRating() != 0) eligibleDeviceCount++;
	}

	// Destroy dummy window
	glfwDestroyWindow(dummyWindow);
	glfwDefaultWindowHints();

	// store only eligible devices
	s_renderDevices.resize(eligibleDeviceCount);
	for (std::uint32_t i = 0; i < eligibleDeviceCount; i++) {
		if (availableRenderDevices[i]->GetRating() == 0) continue;
		s_renderDevices[i] = std::move(availableRenderDevices[i]);
	}
}

} // namespace Junia::Vulkan
