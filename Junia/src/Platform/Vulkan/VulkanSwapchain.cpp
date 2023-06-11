#include "VulkanSwapchain.hpp"
#include "VulkanDevice.hpp"
#include <algorithm>
#include <limits>

namespace Vulkan
{
	extern VulkanDevice* vkDevice;

	VulkanSwapchain::VulkanSwapchain(Junia::Window* window, VkSurfaceKHR surface, uint8_t maxInFlightFrames)
		: maxInFlight(maxInFlightFrames), surface(surface), window(window)
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
			JMath::Vec2ui framebufferSize = window->GetFramebufferSize();
			extent = { framebufferSize.x, framebufferSize.y };
			extent.width = std::clamp(extent.width, surfaceCapabilities.minImageExtent.width, surfaceCapabilities.maxImageExtent.width);
			extent.height = std::clamp(extent.height, surfaceCapabilities.minImageExtent.height, surfaceCapabilities.maxImageExtent.height);
		}

		renderPass = new VulkanRenderPass(format);
		Recreate();

		commandPool = new VulkanCommandPool(vkDevice->GetGraphicsQueueIndex(), maxInFlight);

		// synchronization objects

		imageAvailableSemaphores.resize(maxInFlight);
		renderFinishedSemaphores.resize(maxInFlight);
		inFlightFences.resize(maxInFlight);

		VkSemaphoreCreateInfo semaphoreInfo{ };
		semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

		VkFenceCreateInfo fenceInfo{ };
		fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

		for (size_t i = 0; i < maxInFlight; i++)
		{
			if (vkCreateSemaphore(vkDevice->GetLogical(), &semaphoreInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
				vkCreateSemaphore(vkDevice->GetLogical(), &semaphoreInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS ||
				vkCreateFence(vkDevice->GetLogical(), &fenceInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS)
				throw std::runtime_error("failed to create synchronization objects");
		}
	}

	VulkanSwapchain::~VulkanSwapchain()
	{
		vkDeviceWaitIdle(vkDevice->GetLogical());

		Cleanup();

		delete renderPass;

		for (size_t i = 0; i < maxInFlight; i++)
		{
			vkDestroySemaphore(vkDevice->GetLogical(), imageAvailableSemaphores[i], nullptr);
			vkDestroySemaphore(vkDevice->GetLogical(), renderFinishedSemaphores[i], nullptr);
			vkDestroyFence(vkDevice->GetLogical(), inFlightFences[i], nullptr);
		}

		delete commandPool;
	}

	void VulkanSwapchain::FramebufferResized()
	{
		resized = true;
	}

	void VulkanSwapchain::Cleanup()
	{
		for (auto framebuffer : framebuffers)
			vkDestroyFramebuffer(vkDevice->GetLogical(), framebuffer, nullptr);
		for (VkImageView imageView : imageViews)
			vkDestroyImageView(vkDevice->GetLogical(), imageView, nullptr);
		vkDestroySwapchainKHR(vkDevice->GetLogical(), swapchain, nullptr);
		delete graphicsPipeline;
	}

	void VulkanSwapchain::Recreate()
	{
		JMath::Vec2ui framebufferSize = window->GetFramebufferSize();
		if (framebufferSize.x == 0 || framebufferSize.y == 0) return;

		vkDeviceWaitIdle(vkDevice->GetLogical());

		Cleanup();

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
			extent = { framebufferSize.x, framebufferSize.y };
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
		} else
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

		graphicsPipeline = new VulkanGraphicsPipeline(extent, renderPass);
	}

	void VulkanSwapchain::Draw()
	{
		vkWaitForFences(vkDevice->GetLogical(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

		uint32_t imageIndex;
		VkResult result = vkAcquireNextImageKHR(vkDevice->GetLogical(), swapchain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

		if (result == VK_ERROR_OUT_OF_DATE_KHR)
		{
			Recreate();
			return;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
			throw std::runtime_error("failed to aquire swapchain image");

		vkResetFences(vkDevice->GetLogical(), 1, &inFlightFences[currentFrame]);

		// TODO: remove
		VkCommandBuffer currBuffer = commandPool->GetBuffer(currentFrame);

		commandPool->ResetBuffer(currentFrame);

		commandPool->BeginRecordBuffer(currentFrame);
		renderPass->Begin(framebuffers[imageIndex], extent, currBuffer);

		graphicsPipeline->Bind(currBuffer);
		commandPool->CmdDraw(currentFrame, 3, 1, 0, 0);

		renderPass->End(currBuffer);
		commandPool->EndRecordBuffer(currentFrame);


		VkSubmitInfo submitInfo{ };
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &currBuffer;
		VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;

		if (vkQueueSubmit(vkDevice->GetGraphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS)
			throw std::runtime_error("failed to submit draw command buffer");

		VkPresentInfoKHR presentInfo{ };
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;
		VkSwapchainKHR swapchains[] = { swapchain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapchains;
		presentInfo.pImageIndices = &imageIndex;

		result = vkQueuePresentKHR(vkDevice->GetPresentQueue(), &presentInfo);

		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || resized)
		{
			resized = false;
			Recreate();
		}
		else if (result != VK_SUCCESS)
			throw std::runtime_error("failed to present swapchain image");

		currentFrame = (currentFrame + 1) % maxInFlight;
	}
}
