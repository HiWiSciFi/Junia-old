#include <Junia/Renderer/Surface.hpp>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "../../Platform/Vulkan/VulkanSurface.hpp"
#include <stdexcept>

namespace Junia
{
	Surface* Surface::Create(void* window, WindowApi windowApi, RenderApi renderApi)
	{
		switch (windowApi)
		{
		case Junia::WindowApi::GLFW:
			{
				GLFWwindow* w = reinterpret_cast<GLFWwindow*>(window);
				switch (renderApi)
				{
				case Junia::RenderApi::VULKAN: return new Vulkan::VulkanSurface(w);
				case Junia::RenderApi::NONE: default:
					throw std::runtime_error("unknown render api");
				}
			}
		case Junia::WindowApi::NONE: default:
			throw std::runtime_error("unknown window api");
		}
	}

	Surface::~Surface()
	{

	}
}
