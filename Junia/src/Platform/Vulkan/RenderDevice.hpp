#pragma once

#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include <Junia/Renderer/RenderDevice.hpp>
#include <string>
#include <memory>

#include "Queue.hpp"

namespace Junia::Vulkan {

class RenderDevice : public Junia::RenderDevice {
public:
	RenderDevice(VkPhysicalDevice physicalDevice, GLFWwindow* dummyWindow);
	~RenderDevice();

	virtual void Pick();

	[[nodiscard]] virtual const std::string& GetName() const;

	void WaitIdle();

private:
	static std::vector<std::shared_ptr<Vulkan::RenderDevice>> s_renderDevices;
	static std::shared_ptr<Vulkan::RenderDevice> s_device;

	VkPhysicalDevice physicalDevice;
	VkPhysicalDeviceFeatures features;
	VkPhysicalDeviceProperties properties;
	VkSurfaceFormatKHR surfaceFormat;
	VkDevice device;

	Vulkan::Queue graphicsQueue;
	Vulkan::Queue  presentQueue;
	Vulkan::Queue transferQueue;
	Vulkan::Queue  computeQueue;

	std::string name;
};

} // namespace Junia::Vulkan
