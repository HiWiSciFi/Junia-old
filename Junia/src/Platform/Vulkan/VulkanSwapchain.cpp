#include "VulkanSwapchain.hpp"
#include "VulkanDevice.hpp"

#include <algorithm>
#include <limits>

namespace Vulkan
{
	extern VulkanDevice* vkDevice;

	VulkanSwapchain::VulkanSwapchain(GLFWwindow* window, VkSurfaceKHR surface)
	{
		uint32_t surfaceFormatCount;
		vkGetPhysicalDeviceSurfaceFormatsKHR(vkDevice->GetPhysical(), surface, &surfaceFormatCount, nullptr);
		std::vector<VkSurfaceFormatKHR> surfaceFormats(surfaceFormatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(vkDevice->GetPhysical(), surface, &surfaceFormatCount, surfaceFormats.data());

		VkSurfaceFormatKHR surfaceFormat;
		bool formatFound = false;
		for (const auto& availableFormat : surfaceFormats)
		{
			if (availableFormat.format == VK_FORMAT_B8G8R8A8_SRGB &&
				availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
			{
				surfaceFormat = availableFormat;
				formatFound = true;
				break;
			}
		}
		if (!formatFound) surfaceFormat = surfaceFormats[0];
		format = surfaceFormat.format;

		uint32_t surfacePresentModesCount;
		vkGetPhysicalDeviceSurfacePresentModesKHR(vkDevice->GetPhysical(), surface, &surfacePresentModesCount, nullptr);
		std::vector<VkPresentModeKHR> surfacePresentModes(surfacePresentModesCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(vkDevice->GetPhysical(), surface, &surfacePresentModesCount, surfacePresentModes.data());

		// choose presentation mode
		// available modes:
		//   - VK_PRESENT_MODE_IMMEDIATE_KHR               | (V-Sync Off) Immediate push
		//   - VK_PRESENT_MODE_MAILBOX_KHR                 | (No gpu block and no tearing) Push on v-blank and always newest
		//   - VK_PRESENT_MODE_FIFO_KHR [always supported] | (V-Sync On) Push on v-blank and append to queue
		//   - VK_PRESENT_MODE_FIFO_RELAXED_KHR            | Immediate push if v-blank was missed, V-Sync otherwise (tearing when rendering too slowly)
		VkPresentModeKHR presentMode = VK_PRESENT_MODE_MAX_ENUM_KHR;
		for (const auto& availablePresentMode : surfacePresentModes)
		{
			if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				presentMode = availablePresentMode;
				break;
			}
		}
		if (presentMode == VK_PRESENT_MODE_MAX_ENUM_KHR) presentMode = VK_PRESENT_MODE_FIFO_KHR;

		VkSurfaceCapabilitiesKHR surfaceCapabilities;
		vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkDevice->GetPhysical(), surface, &surfaceCapabilities);

		if (surfaceCapabilities.currentExtent.width != std::numeric_limits<uint32_t>::max())
			extent = surfaceCapabilities.currentExtent;
		else
		{
			int glfwFramebufferWidth;
			int glfwFramebufferHeight;
			glfwGetFramebufferSize(window, &glfwFramebufferWidth, &glfwFramebufferHeight);
			extent = { static_cast<uint32_t>(glfwFramebufferWidth), static_cast<uint32_t>(glfwFramebufferHeight) };
			extent.width = std::clamp(extent.width, surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width);
			extent.height = std::clamp(extent.height, surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height);
		}

		uint32_t imageCount = surfaceCapabilities.minImageCount + 1;
		if (surfaceCapabilities.maxImageCount > 0 && imageCount > surfaceCapabilities.maxImageCount)
			imageCount = surfaceCapabilities.maxImageCount;

		VkSwapchainCreateInfoKHR scCreateInfo{ };
		scCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		scCreateInfo.surface = surface;
		scCreateInfo.minImageCount = imageCount;
		scCreateInfo.imageFormat = format;
		scCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
		scCreateInfo.imageExtent = extent;
		scCreateInfo.imageArrayLayers = 1;
		scCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		uint32_t queueFamilyIndices[] = { vkDevice->GetGraphicsQueueIndex(), vkDevice->GetPresentQueueIndex() };
		if (queueFamilyIndices[0] != queueFamilyIndices[1])
		{
			scCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
			scCreateInfo.queueFamilyIndexCount = 2;
			scCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
		}
		else
		{
			scCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
			scCreateInfo.queueFamilyIndexCount = 0;
			scCreateInfo.pQueueFamilyIndices = nullptr;
		}
		scCreateInfo.preTransform = surfaceCapabilities.currentTransform;
		scCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		scCreateInfo.presentMode = presentMode;
		scCreateInfo.clipped = VK_TRUE;
		scCreateInfo.oldSwapchain = nullptr;

		if (vkCreateSwapchainKHR(vkDevice->GetLogical(), &scCreateInfo, nullptr, &swapchain) != VK_SUCCESS)
			throw std::runtime_error("failed to create swapchain");

		// get swapchain images
		vkGetSwapchainImagesKHR(vkDevice->GetLogical(), swapchain, &imageCount, nullptr);
		images.resize(imageCount);
		vkGetSwapchainImagesKHR(vkDevice->GetLogical(), swapchain, &imageCount, images.data());

		// generate image views
		imageViews.resize(images.size());
		for (size_t i = 0; i < images.size(); i++)
		{
			VkImageViewCreateInfo viewCreateInfo{ };
			viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
			viewCreateInfo.image = reinterpret_cast<VkImage>(images[i]);
			viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
			viewCreateInfo.format = format;
			viewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
			viewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
			viewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
			viewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
			viewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
			viewCreateInfo.subresourceRange.baseMipLevel = 0;
			viewCreateInfo.subresourceRange.levelCount = 1;
			viewCreateInfo.subresourceRange.baseArrayLayer = 0;
			viewCreateInfo.subresourceRange.layerCount = 1;

			if (vkCreateImageView(vkDevice->GetLogical(), &viewCreateInfo, nullptr, &imageViews[i]) != VK_SUCCESS)
				throw std::runtime_error("failed to create image view");
		}

		renderPass = new VulkanRenderPass(format);
		graphicsPipeline = new VulkanGraphicsPipeline(extent, renderPass);

		framebuffers.resize(imageViews.size());
		for (size_t i = 0; i < imageViews.size(); i++)
		{
			VkImageView attachments[] = { imageViews[i] };

			VkFramebufferCreateInfo framebufferInfo{ };
			framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
			framebufferInfo.renderPass = renderPass->Get();
			framebufferInfo.attachmentCount = 1;
			framebufferInfo.pAttachments = attachments;
			framebufferInfo.width = extent.width;
			framebufferInfo.height = extent.height;
			framebufferInfo.layers = 1;

			if (vkCreateFramebuffer(vkDevice->GetLogical(), &framebufferInfo, nullptr, &framebuffers[i]) != VK_SUCCESS)
				throw std::runtime_error("failed to create framebuffer");
		}

		commandPool = new VulkanCommandPool();
	}

	VulkanSwapchain::~VulkanSwapchain()
	{
		delete commandPool;
		for (auto framebuffer : framebuffers)
			vkDestroyFramebuffer(vkDevice->GetLogical(), framebuffer, nullptr);
		delete renderPass;
		delete graphicsPipeline;
		for (VkImageView imageView : imageViews)
			vkDestroyImageView(vkDevice->GetLogical(), imageView, nullptr);
		vkDestroySwapchainKHR(vkDevice->GetLogical(), swapchain, nullptr);
	}

	void VulkanSwapchain::Draw()
	{
		uint32_t imageIndex = 0;
		commandPool->BeginRecordCommandBuffer();
		renderPass->Begin(framebuffers[imageIndex], extent, commandPool->GetBuffer());
		graphicsPipeline->Bind(commandPool->GetBuffer());
		vkCmdDraw(commandPool->GetBuffer(), 3, 1, 0, 0);
		renderPass->End(commandPool->GetBuffer());
		commandPool->EndRecordCommandBuffer();
	}
}
