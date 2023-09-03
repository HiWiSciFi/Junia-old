#include <vulkan/vulkan.hpp>
#include <GLFW/glfw3.h>
#include "VulkanSurface.hpp"
#include <stdexcept>
#include "VulkanDevice.hpp"
#include "VulkanMesh.hpp"
#include "VulkanMaterial.hpp"

namespace Vulkan {

extern VkInstance vkInstance;
extern VulkanDevice* vkDevice;

static const uint32_t MAX_FRAMES_IN_FLIGHT = 2;

void VulkanSurface::CleanupSwapchain() {
	vkDevice->WaitIdle();

	// cleanup swapchain
	for (size_t i = 0; i < swapchainFramebuffers.size(); i++) {
		vkDestroyFramebuffer(vkDevice->GetLogical(), swapchainFramebuffers[i], nullptr);
		vkDestroyImageView(vkDevice->GetLogical(), swapchainImageViews[i], nullptr);
	}
	vkDestroySwapchainKHR(vkDevice->GetLogical(), swapchain, nullptr);
}

VulkanSurface::VulkanSurface(Junia::Window* window, VSyncMode vsync) : window(window) {
	// create window surface
	if (glfwCreateWindowSurface(vkInstance, static_cast<GLFWwindow*>(window->GetNative()), nullptr, &surface) != VK_SUCCESS)
		throw std::runtime_error("failed to create window surface");

	// get present modes
	uint32_t presentModeCount;
	if (vkGetPhysicalDeviceSurfacePresentModesKHR(vkDevice->GetPhysical(), surface, &presentModeCount, nullptr) != VK_SUCCESS)
		throw std::runtime_error("failed to get surface presentation modes");
	if (presentModeCount == 0) throw std::runtime_error("no surface presentation modes available");
	std::vector<VkPresentModeKHR> presentModes(presentModeCount);
	if (vkGetPhysicalDeviceSurfacePresentModesKHR(vkDevice->GetPhysical(), surface, &presentModeCount, presentModes.data()) != VK_SUCCESS)
		throw std::runtime_error("failed to get surface presentation modes");

	// choose present mode
	VkPresentModeKHR preferredPresentMode = VK_PRESENT_MODE_FIFO_KHR;
	switch (vsync) {
	case Junia::Surface::VSyncMode::OFF:              VK_PRESENT_MODE_IMMEDIATE_KHR;    break;
	case Junia::Surface::VSyncMode::ON_QUEUE:         VK_PRESENT_MODE_FIFO_KHR;         break;
	case Junia::Surface::VSyncMode::ON_QUEUE_RELAXED: VK_PRESENT_MODE_FIFO_RELAXED_KHR; break;
	case Junia::Surface::VSyncMode::ON_QUEUE_REPLACE: VK_PRESENT_MODE_MAILBOX_KHR;      break;
	default: break;
	}
	presentMode = VK_PRESENT_MODE_MAX_ENUM_KHR;
	for (const VkPresentModeKHR& aMode : presentModes) {
		if (aMode == preferredPresentMode) {
			presentMode = aMode;
			break;
		}
	}
	if (presentMode = VK_PRESENT_MODE_MAX_ENUM_KHR) presentMode = VK_PRESENT_MODE_FIFO_KHR;

	// get surface capabilities
	if (vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkDevice->GetPhysical(), surface, &capabilities) != VK_SUCCESS)
		throw std::runtime_error("failed to get surface capabilities");

	// choose swap extent
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		resolution = capabilities.currentExtent;
	} else {
		resolution = {
			std::clamp(window->GetFramebufferSize().x, capabilities.minImageExtent.width, capabilities.maxImageExtent.width),
			std::clamp(window->GetFramebufferSize().y, capabilities.minImageExtent.height, capabilities.maxImageExtent.height)
		};
	}

	// viewport and scissor scaling (full window)
	viewport.x = 0.0f;
	viewport.y = 0.0f;
	viewport.width = static_cast<float>(resolution.width);
	viewport.height = static_cast<float>(resolution.height);
	viewport.minDepth = 0.0f;
	viewport.maxDepth = 1.0f;
	scissor.offset = { 0, 0 };
	scissor.extent = resolution;

	// create render pass
	renderPass = new VulkanRenderPass(JMath::Vec4f(0.0f, 0.0f, 0.0f, 1.0f));

	// select swapchain image count
	imageCount = capabilities.minImageCount + 1;
	if (capabilities.maxImageCount != 0)
		imageCount = std::clamp(imageCount, capabilities.minImageCount, capabilities.maxImageCount);

	CreateSwapchain();

	// create command pool
	VkCommandPoolCreateInfo poolCreateInfo{ };
	poolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	poolCreateInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	poolCreateInfo.queueFamilyIndex = vkDevice->GetGraphicsQueueIndex();
	if (vkCreateCommandPool(vkDevice->GetLogical(), &poolCreateInfo, nullptr, &renderingCommandPool) != VK_SUCCESS)
		throw std::runtime_error("failed to create rendering command pool");

	// allocate command buffers
	renderingCommandBuffers.resize(MAX_FRAMES_IN_FLIGHT);
	VkCommandBufferAllocateInfo bufferAllocInfo{ };
	bufferAllocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	bufferAllocInfo.commandPool = renderingCommandPool;
	bufferAllocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
	bufferAllocInfo.commandBufferCount = static_cast<uint32_t>(renderingCommandBuffers.size());
	if (vkAllocateCommandBuffers(vkDevice->GetLogical(), &bufferAllocInfo, renderingCommandBuffers.data()) != VK_SUCCESS)
		throw std::runtime_error("failed to allocate rendering command buffers");

	// create sync objects
	imageAvailableSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	renderFinishedSemaphores.resize(MAX_FRAMES_IN_FLIGHT);
	inFlightFences.resize(MAX_FRAMES_IN_FLIGHT);
	VkSemaphoreCreateInfo semaphoreCreateInfo{ };
	semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	VkFenceCreateInfo fenceCreateInfo{ };
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceCreateInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

	for (uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		if (vkCreateSemaphore(vkDevice->GetLogical(), &semaphoreCreateInfo, nullptr, &imageAvailableSemaphores[i]) != VK_SUCCESS ||
			vkCreateSemaphore(vkDevice->GetLogical(), &semaphoreCreateInfo, nullptr, &renderFinishedSemaphores[i]) != VK_SUCCESS)
			throw std::runtime_error("failed to create render semaphores");
		if (vkCreateFence(vkDevice->GetLogical(), &fenceCreateInfo, nullptr, &inFlightFences[i]) != VK_SUCCESS)
			throw std::runtime_error("failed to create render fence");
	}
}

VulkanSurface::~VulkanSurface() {
	vkDevice->WaitIdle();
	CleanupSwapchain();
	for (uint32_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
		vkDestroySemaphore(vkDevice->GetLogical(), imageAvailableSemaphores[i], nullptr);
		vkDestroySemaphore(vkDevice->GetLogical(), renderFinishedSemaphores[i], nullptr);
		vkDestroyFence(vkDevice->GetLogical(), inFlightFences[i], nullptr);
	}
	vkDestroyCommandPool(vkDevice->GetLogical(), renderingCommandPool, nullptr);
	delete renderPass;
	vkDestroySurfaceKHR(vkInstance, surface, nullptr);
}

void VulkanSurface::CreateSwapchain() {
	resolution.width = window->GetFramebufferSize().x;
	resolution.height = window->GetFramebufferSize().y;
	viewport.width = static_cast<float>(resolution.width);
	viewport.height = static_cast<float>(resolution.height);
	scissor.extent = resolution;

	// create swapchain
	VkSwapchainCreateInfoKHR swapchainCreateInfo{ };
	swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	swapchainCreateInfo.surface = surface;
	swapchainCreateInfo.minImageCount = imageCount;
	swapchainCreateInfo.imageFormat = vkDevice->GetSurfaceFormat().format;
	swapchainCreateInfo.imageColorSpace = vkDevice->GetSurfaceFormat().colorSpace;
	swapchainCreateInfo.imageExtent = resolution;
	swapchainCreateInfo.imageArrayLayers = 1;
	swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	uint32_t queueFamilyIndices[] = { vkDevice->GetGraphicsQueueIndex(), vkDevice->GetPresentQueueIndex() };
	if (queueFamilyIndices[0] != queueFamilyIndices[1]) {
		swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		swapchainCreateInfo.queueFamilyIndexCount = 2;
		swapchainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
	} else swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	swapchainCreateInfo.preTransform = capabilities.currentTransform;
	swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	swapchainCreateInfo.presentMode = presentMode;
	swapchainCreateInfo.clipped = VK_TRUE;
	swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;
	if (vkCreateSwapchainKHR(vkDevice->GetLogical(), &swapchainCreateInfo, nullptr, &swapchain) != VK_SUCCESS)
		throw std::runtime_error("failed to create swapchain");

	// retrieve swapchain images
	if (vkGetSwapchainImagesKHR(vkDevice->GetLogical(), swapchain, &imageCount, nullptr) != VK_SUCCESS)
		throw std::runtime_error("failed to retrieve swapchain images");
	swapchainImages.resize(imageCount);
	if (vkGetSwapchainImagesKHR(vkDevice->GetLogical(), swapchain, &imageCount, swapchainImages.data()) != VK_SUCCESS)
		throw std::runtime_error("failed to retrieve swapchain images");

	// create swapchain image views and framebuffers
	swapchainImageViews.resize(swapchainImages.size());
	swapchainFramebuffers.resize(swapchainImages.size());
	VkImageViewCreateInfo imageViewCreateInfo{ };
	imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	imageViewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	imageViewCreateInfo.format = vkDevice->GetSurfaceFormat().format;
	imageViewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
	imageViewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
	imageViewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
	imageViewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
	imageViewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
	imageViewCreateInfo.subresourceRange.levelCount = 1;
	imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
	imageViewCreateInfo.subresourceRange.layerCount = 1;
	VkFramebufferCreateInfo framebufferCreateInfo{ };
	framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebufferCreateInfo.renderPass = renderPass->Get();
	framebufferCreateInfo.attachmentCount = 1;
	framebufferCreateInfo.width = resolution.width;
	framebufferCreateInfo.height = resolution.height;
	framebufferCreateInfo.layers = 1;
	for (size_t i = 0; i < swapchainImages.size(); i++) {
		imageViewCreateInfo.image = swapchainImages[i];
		if (vkCreateImageView(vkDevice->GetLogical(), &imageViewCreateInfo, nullptr, &swapchainImageViews[i]) != VK_SUCCESS)
			throw std::runtime_error("failed to create swapchain image view");
		framebufferCreateInfo.pAttachments = &swapchainImageViews[i];
		if (vkCreateFramebuffer(vkDevice->GetLogical(), &framebufferCreateInfo, nullptr, &swapchainFramebuffers[i]) != VK_SUCCESS)
			throw std::runtime_error("failed to create framebuffer");
	}
}

JMath::Vec2ui VulkanSurface::GetResolution() {
	return JMath::Vec2ui(resolution.width, resolution.height);
}

Junia::Surface::VSyncMode VulkanSurface::GetVSyncMode() {
	switch (presentMode) {
	case VK_PRESENT_MODE_IMMEDIATE_KHR:    return VSyncMode::OFF;
	case VK_PRESENT_MODE_FIFO_KHR:         return VSyncMode::ON_QUEUE;
	case VK_PRESENT_MODE_FIFO_RELAXED_KHR: return VSyncMode::ON_QUEUE_RELAXED;
	case VK_PRESENT_MODE_MAILBOX_KHR:      return VSyncMode::ON_QUEUE_REPLACE;
	default:                               return VSyncMode::OFF;
	}
}

void VulkanSurface::FramebufferResized(JMath::Vec2ui newSize) {
	framebufferResized = true;
}

void VulkanSurface::BeginDraw() {
	if (vkWaitForFences(vkDevice->GetLogical(), 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX) != VK_SUCCESS)
		throw std::runtime_error("failed to wait for flight fence");

	VkResult result;
	do {
		result = vkAcquireNextImageKHR(vkDevice->GetLogical(), swapchain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &currentImageIndex);
		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			CleanupSwapchain();
			CreateSwapchain();
		} else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire image from the swapchain");
		}
	} while(result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR);

	if (vkResetFences(vkDevice->GetLogical(), 1, &inFlightFences[currentFrame]) != VK_SUCCESS)
		throw std::runtime_error("failed to reset in flight fence");

	if (vkResetCommandBuffer(renderingCommandBuffers[currentFrame], 0) != VK_SUCCESS)
		throw std::runtime_error("faied to reset rendering command buffer");
	VkCommandBufferBeginInfo renderingBufferBeginInfo{ };
	renderingBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	if (vkBeginCommandBuffer(renderingCommandBuffers[currentFrame], &renderingBufferBeginInfo) != VK_SUCCESS)
		throw std::runtime_error("failed to begin recording rendering command buffer");

	renderPass->Begin(renderingCommandBuffers[currentFrame], swapchainFramebuffers[currentImageIndex], scissor.extent);

	vkCmdSetViewport(renderingCommandBuffers[currentFrame], 0, 1, &viewport);
	vkCmdSetScissor(renderingCommandBuffers[currentFrame], 0, 1, &scissor);
}

void VulkanSurface::Draw(Junia::ComponentRef<Junia::MeshRenderer> package) {
	std::shared_ptr<VulkanMesh> mesh = std::dynamic_pointer_cast<VulkanMesh>(package->mesh);
	std::shared_ptr<VulkanMaterial> material = std::dynamic_pointer_cast<VulkanMaterial>(package->material);
	material->BindPipeline(renderingCommandBuffers[currentFrame]);
	mesh->BindVertexBuffer(renderingCommandBuffers[currentFrame]);
	mesh->BindIndexBuffer(renderingCommandBuffers[currentFrame]);
	vkCmdDrawIndexed(renderingCommandBuffers[currentFrame], mesh->GetIndices().size() * 3, 1, 0, 0, 0);
	//vkCmdDraw(renderingCommandBuffers[currentFrame], mesh->GetVertices().size(), 1, 0, 0);
}

void VulkanSurface::EndDraw() {
	renderPass->End(renderingCommandBuffers[currentFrame]);

	if (vkEndCommandBuffer(renderingCommandBuffers[currentFrame]) != VK_SUCCESS)
		throw std::runtime_error("failed to record rendering command buffer");

	VkSubmitInfo submitInfo{ };
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
	submitInfo.waitSemaphoreCount = 1;
	submitInfo.pWaitSemaphores = &imageAvailableSemaphores[currentFrame];
	submitInfo.pWaitDstStageMask = waitStages;
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &renderingCommandBuffers[currentFrame];
	submitInfo.signalSemaphoreCount = 1;
	submitInfo.pSignalSemaphores = &renderFinishedSemaphores[currentFrame];
	if (vkQueueSubmit(vkDevice->GetGraphicsQueue(), 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS)
		throw std::runtime_error("failed to submit draw commands to queue");

	VkPresentInfoKHR presentInfo{ };
	presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &renderFinishedSemaphores[currentFrame];
	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = &swapchain;
	presentInfo.pImageIndices = &currentImageIndex;
	VkResult result = vkQueuePresentKHR(vkDevice->GetPresentQueue(), &presentInfo);
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
		framebufferResized = false;
		CleanupSwapchain();
		CreateSwapchain();
	} else if (result != VK_SUCCESS) {
		throw std::runtime_error("failed to present swapchain to screen");
	}

	currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

} // namespace Vulkan
