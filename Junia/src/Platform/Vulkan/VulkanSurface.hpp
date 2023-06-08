#pragma once

#include <vulkan/vulkan.hpp>
#include <Junia/Renderer/Surface.hpp>
#include <Junia/Core/Window.hpp>
#include "VulkanSwapchain.hpp"

namespace Vulkan
{
	class VulkanSurface : public Junia::Surface
	{
	private:
		VkSurfaceKHR surface = nullptr;
		VulkanSwapchain* swapchain = nullptr;

	public:
		VulkanSurface(Junia::Window* window);
		~VulkanSurface() override;

		void FramebufferResized() override;
		void Draw() override;
	};
}
