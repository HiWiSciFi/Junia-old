#include "RenderDevice.hpp"

#include <set>
#include <GLFW/glfw3.h>

#include "Instance.hpp"
#include "../../Junia/Core/InternalLoggers.hpp"

#ifdef NDEBUG
static constexpr bool c_debug = false;
#else
static constexpr bool c_debug = true;
#endif

namespace Junia::Vulkan {

std::vector<std::shared_ptr<Vulkan::RenderDevice>> Vulkan::RenderDevice::s_renderDevices{ };
std::shared_ptr<Vulkan::RenderDevice> s_device;

void RenderDevice::Pick() {
	if (GetRating() == 0) throw std::runtime_error("selected render device is not suitable");

	// Create logical device

	// Get unique queues
	std::set<std::uint32_t> uniqueQueueFamilies{ };
	uniqueQueueFamilies.insert(this->graphicsQueue.GetFamilyIndex());
	uniqueQueueFamilies.insert(this->presentQueue .GetFamilyIndex());
	if (this->transferQueue.IsValid()) uniqueQueueFamilies.insert(this->transferQueue.GetFamilyIndex());
	if (this->computeQueue .IsValid()) uniqueQueueFamilies.insert(this->computeQueue .GetFamilyIndex());

	// Create queue create infos
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos{ };
	queueCreateInfos.reserve(uniqueQueueFamilies.size());
	float queuePriorities[] = { 1.0f };
	for (auto queueFamily : uniqueQueueFamilies) {
		VkDeviceQueueCreateInfo queueCreateInfo = {
			.sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
			.queueFamilyIndex = queueFamily,
			.queueCount       = 1,
			.pQueuePriorities = queuePriorities
		};
		queueCreateInfos.push_back(queueCreateInfo);
	}

	// enabled layers
	std::vector<const char*> enabledLayers = { "VK_LAYER_KHRONOS_validation" };

	// required extensions
	std::vector<const char*> requiredDeviceExtensions = { VK_KHR_SWAPCHAIN_EXTENSION_NAME };

	// required features
	VkPhysicalDeviceFeatures requiredDeviceFeatures = { };

	// Create device create info
	VkDeviceCreateInfo deviceCreateInfo = {
		.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.queueCreateInfoCount    = static_cast<std::uint32_t>(queueCreateInfos.size()),
		.pQueueCreateInfos       = queueCreateInfos.data(),
		.enabledLayerCount       = c_debug ? static_cast<std::uint32_t>(enabledLayers.size()) : 0,
		.ppEnabledLayerNames     = enabledLayers.data(),
		.enabledExtensionCount   = static_cast<std::uint32_t>(requiredDeviceExtensions.size()),
		.ppEnabledExtensionNames = requiredDeviceExtensions.data(),
		.pEnabledFeatures        = &requiredDeviceFeatures
	};

	// Create device
	if (vkCreateDevice(this->physicalDevice, &deviceCreateInfo, nullptr, &this->device) != VK_SUCCESS)
		throw std::runtime_error("failed to create logical vulkan device");

	// Set Queue objects
	this->graphicsQueue.UpdateQueue(this->device);
	this->presentQueue .UpdateQueue(this->device);
	this->transferQueue.UpdateQueue(this->device);
	this->computeQueue .UpdateQueue(this->device);
}

const std::string& Vulkan::RenderDevice::GetName() const {
	return this->name;
}

void RenderDevice::WaitIdle() {
	vkDeviceWaitIdle(this->device);
}

Vulkan::RenderDevice::RenderDevice(VkPhysicalDevice physicalDevice, GLFWwindow* dummyWindow)
	: physicalDevice(physicalDevice), device(VK_NULL_HANDLE), surfaceFormat() {
	// Get features and properties
	vkGetPhysicalDeviceFeatures(this->physicalDevice, &this->features);
	vkGetPhysicalDeviceProperties(this->physicalDevice, &this->properties);
	switch (properties.deviceType) {
		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:   SetType(Junia::RenderDeviceType::DISCRETE_GPU);   break;
		case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:    SetType(Junia::RenderDeviceType::VIRTUAL_GPU);    break;
		case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: SetType(Junia::RenderDeviceType::INTEGRATED_GPU); break;
		case VK_PHYSICAL_DEVICE_TYPE_CPU:            SetType(Junia::RenderDeviceType::CPU);            break;
		case VK_PHYSICAL_DEVICE_TYPE_OTHER:          SetType(Junia::RenderDeviceType::OTHER);          break;
	}
	SetRating((static_cast<std::uint32_t>(GetType()) * 10000) + 1 + properties.limits.maxImageDimension2D);

	// Query device extension support
	std::uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(this->physicalDevice, nullptr, &extensionCount, nullptr);
	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(this->physicalDevice, nullptr, &extensionCount, availableExtensions.data());
	SetRating(GetRating() + extensionCount);

	// Query required device extensions
	std::set<std::string> requiredExtensions{ VK_KHR_SWAPCHAIN_EXTENSION_NAME };
	for (const auto& extension : availableExtensions) requiredExtensions.erase(extension.extensionName);
	if (!requiredExtensions.empty()) {
		SetRating(0);
		return;
	}

	// Query queue families
	std::uint32_t queueFamilyCount;
	vkGetPhysicalDeviceQueueFamilyProperties(this->physicalDevice, &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamilyProperties(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(this->physicalDevice, &queueFamilyCount, queueFamilyProperties.data());

	// Create dummy surface for surface dependent features
	VkSurfaceKHR dummySurface;
	bool failed = true;
	if (glfwCreateWindowSurface(Vulkan::Instance::Get(), dummyWindow, VK_NULL_HANDLE, &dummySurface) != VK_SUCCESS)
		throw std::runtime_error("failed to create dummy surface for render device rating");

	// will only run once -- used for break to cleanup code
	do {
		// Find queue families
		for (std::uint32_t i = 0; i < queueFamilyCount; i++) {
			if (!this->graphicsQueue.IsValid() && queueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) this->graphicsQueue = Vulkan::Queue(i, VK_NULL_HANDLE);
			if (!this->transferQueue.IsValid() && queueFamilyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT) this->transferQueue = Vulkan::Queue(i, VK_NULL_HANDLE);
			if (!this->computeQueue .IsValid() && queueFamilyProperties[i].queueFlags & VK_QUEUE_COMPUTE_BIT ) this->computeQueue  = Vulkan::Queue(i, VK_NULL_HANDLE);
			VkBool32 presentationSupport = false;
			if (!this->presentQueue.IsValid() && vkGetPhysicalDeviceSurfaceSupportKHR(this->physicalDevice, i, dummySurface, &presentationSupport), presentationSupport)
				this->presentQueue = Vulkan::Queue(i, VK_NULL_HANDLE);
		}
		SetRating(GetRating() + (this->transferQueue.IsValid() * 200) + (this->computeQueue.IsValid() * 100));

		// Debug printing for available queue families
		/*VKLOG_INFO << "Queue Families:";
		for (std::uint32_t i = 0; i < queueFamilyCount; i++) {
			auto out = VKLOG_INFO;
			out << "  - " << i << " Queues: " << queueFamilyProperties[i].queueCount << " { ";
			if (queueFamilyProperties[i].queueFlags &         VK_QUEUE_GRAPHICS_BIT) out << "Graphics ";
			if (queueFamilyProperties[i].queueFlags &          VK_QUEUE_COMPUTE_BIT) out << "Compute ";
			if (queueFamilyProperties[i].queueFlags &         VK_QUEUE_TRANSFER_BIT) out << "Transfer ";
			if (queueFamilyProperties[i].queueFlags &   VK_QUEUE_SPARSE_BINDING_BIT) out << "Sparse ";
			if (queueFamilyProperties[i].queueFlags &        VK_QUEUE_PROTECTED_BIT) out << "Protected ";
			if (queueFamilyProperties[i].queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR) out << "Decode ";
			if (queueFamilyProperties[i].queueFlags &  VK_QUEUE_OPTICAL_FLOW_BIT_NV) out << "Optical ";
			VkBool32 present;
			vkGetPhysicalDeviceSurfaceSupportKHR(this->physicalDevice, i, dummySurface, &present);
			if (present) out << "Present ";
			out << "}";
		}*/

		// Get surface formats
		std::uint32_t formatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(this->physicalDevice, dummySurface, &formatCount, nullptr);
		if (formatCount == 0) break;
		std::vector<VkSurfaceFormatKHR> formats(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(this->physicalDevice, dummySurface, &formatCount, formats.data());

		// Choose surface format
		bool formatChosen = false;
		for (const auto& format : formats) {
			if (format.format == VK_FORMAT_B8G8R8A8_SRGB && format.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
				this->surfaceFormat = format;
				formatChosen = true;
				break;
			}
		}
		if (!formatChosen) this->surfaceFormat = formats[0];

		// At least one present mode required
		std::uint32_t presentModeCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(this->physicalDevice, dummySurface, &presentModeCount, nullptr);
		if (presentModeCount == 0) break;

	} while (failed = false); // NOTE: assignment intended

	// Cleanup dummy surface
	vkDestroySurfaceKHR(Vulkan::Instance::Get(), dummySurface, nullptr);

	// If not eligible
	if (failed
		|| !this->graphicsQueue.IsValid()
		|| !this->presentQueue .IsValid()) {
		SetRating(0);
		return;
	}

	// Increase rating if graphics queue shares family with present queue
	if (this->graphicsQueue.GetFamilyIndex() == presentQueue.GetFamilyIndex()) SetRating(GetRating() + 100);

	// Copy name into string
	this->name = std::string(properties.deviceName);
}

Vulkan::RenderDevice::~RenderDevice() {
	vkDestroyDevice(this->device, nullptr);
}

} // namespace Junia::Vulkan
