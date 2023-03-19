#include <Junia/Renderer/Surface.hpp>
#include "../../Platform/Vulkan/VulkanSurface.hpp"
#include <stdexcept>

namespace Junia
{
	Surface* Surface::Create(Junia::Window* window, WindowApi windowApi, RenderApi renderApi)
	{
		switch (windowApi)
		{
		case Junia::WindowApi::GLFW:
			{
				switch (renderApi)
				{
				case Junia::RenderApi::VULKAN: return new Vulkan::VulkanSurface(window);
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
