#pragma once

#include <vulkan/vulkan.hpp>
#include <Junia/Renderer/Surface.hpp>
#include "VulkanRenderPackage.hpp"
#include <Junia/Core/Window.hpp>
#include "VulkanRenderPass.hpp"
#include <vector>

namespace Vulkan {

class VulkanSurface : public Junia::Surface {
private:
	VkSurfaceKHR surface = VK_NULL_HANDLE;
	VkSurfaceFormatKHR surfaceFormat{ };
	VkPresentModeKHR presentMode = VK_PRESENT_MODE_MAX_ENUM_KHR;
	VkExtent2D resolution{ };
	VkViewport viewport{ };
	VkRect2D scissor{ };

	VkSwapchainKHR swapchain = VK_NULL_HANDLE;
	std::vector<VkImage> swapchainImages{ };
	std::vector<VkImageView> swapchainImageViews{ };
	std::vector<VkFramebuffer> swapchainFramebuffers{ };
	std::vector<VkSemaphore> imageAvailableSemaphores{ };
	std::vector<VkSemaphore> renderFinishedSemaphores{ };
	std::vector<VkFence> inFlightFences{ };
	uint32_t currentImageIndex = 0;
	uint32_t currentFrame = 0;

	VkCommandPool renderingCommandPool = VK_NULL_HANDLE;
	std::vector<VkCommandBuffer> renderingCommandBuffers{ };

public:
	VulkanSurface(Junia::Window* window, JMath::Vec2ui resolution, VSyncMode vsync);
	~VulkanSurface() override;

	JMath::Vec2ui GetResolution() override;
	VSyncMode GetVSyncMode() override;

	void FramebufferResized(JMath::Vec2ui newSize) override;

	void BeginDraw() override;
	void Draw(std::shared_ptr<Junia::RenderPackage> package) override;
	void EndDraw() override;
};

} // namespace Vulkan
