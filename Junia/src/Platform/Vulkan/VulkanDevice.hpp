#pragma once

#include <vulkan/vulkan.hpp>
#include <Junia/Renderer/RenderDevice.hpp>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>

namespace Vulkan {

class VulkanDevice : public Junia::RenderDevice {
private:
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice logicalDevice = VK_NULL_HANDLE;

	std::optional<uint32_t> graphicsQueueIndex; VkQueue graphicsQueue = VK_NULL_HANDLE;
	std::optional<uint32_t>  presentQueueIndex; VkQueue presentQueue  = VK_NULL_HANDLE;
	std::optional<uint32_t> transferQueueIndex; VkQueue transferQueue = VK_NULL_HANDLE;
	std::optional<uint32_t>  computeQueueIndex; VkQueue computeQueue  = VK_NULL_HANDLE;

	VkPhysicalDeviceProperties deviceProperties{ };
	VkPhysicalDeviceFeatures     deviceFeatures{ };
	VkSurfaceFormatKHR surfaceFormat{ };

	std::string deviceName{ };

public:
	VulkanDevice(VkPhysicalDevice vkDevice);
	~VulkanDevice();

	void Pick() override;

	void WaitIdle();
	void GraphicsQueueWaitIdle();
	void PresentQueueWaitIdle();
	void TransferQueueWaitIdle();
	void ComputeQueueWaitIdle();

	inline VkPhysicalDevice GetPhysical() const { return physicalDevice; }
	inline VkDevice GetLogical() const { return logicalDevice; }

	inline uint32_t GetGraphicsQueueIndex() const { return graphicsQueueIndex.value(); }
	inline uint32_t GetPresentQueueIndex() const { return presentQueueIndex.value(); }
	inline uint32_t GetTransferQueueIndex() const { return transferQueueIndex.value(); }
	inline uint32_t GetComputeQueueIndex() const { return computeQueueIndex.value(); }

	inline VkSurfaceFormatKHR GetSurfaceFormat() const { return surfaceFormat; }

	inline VkQueue GetGraphicsQueue() const { return graphicsQueue; }
	inline VkQueue GetPresentQueue()  const { return  presentQueue; }
	inline VkQueue GetTransferQueue() const { return transferQueue; }
	inline VkQueue GetComputeQueue()  const { return  computeQueue; }

	const std::string& GetName() const { return deviceName; }
};

} // namespace Vulkan
