#pragma once

#include <Junia/Renderer/RenderDevice.hpp>
#include <vulkan/vulkan.h>
#include <optional>
#include <stdexcept>

namespace Vulkan
{
	class VulkanDevice : public Junia::RenderDevice
	{
	private:
		VkPhysicalDevice physicalDevice = nullptr;
		VkDevice logicalDevice = nullptr;

		std::optional<uint32_t> graphicsQueueIndex; VkQueue graphicsQueue = nullptr;
		std::optional<uint32_t>  presentQueueIndex; VkQueue presentQueue  = nullptr;
		std::optional<uint32_t>  computeQueueIndex; VkQueue computeQueue  = nullptr;

		VkPhysicalDeviceProperties deviceProperties;
		VkPhysicalDeviceFeatures deviceFeatures;

	public:
		VulkanDevice(VkPhysicalDevice vkDevice);
		~VulkanDevice();

		void Pick() override;

		inline VkPhysicalDevice GetPhysical() const { return physicalDevice; }
		inline VkDevice GetLogical() const { return logicalDevice; }

		inline uint32_t GetGraphicsQueueIndex() const
		{
			if (graphicsQueueIndex.has_value()) return graphicsQueueIndex.value();
			throw std::runtime_error("failed to find graphics queue family index");
		}

		inline uint32_t GetPresentQueueIndex() const
		{
			if (presentQueueIndex.has_value()) return presentQueueIndex.value();
			throw std::runtime_error("failed to find present queue family index");
		}

		inline uint32_t GetComputeQueueIndex() const
		{
			if (computeQueueIndex.has_value()) return computeQueueIndex.value();
			throw std::runtime_error("failed to find compute queue family index");
		}

		const char* GetName() const { return deviceProperties.deviceName; }
	};
}