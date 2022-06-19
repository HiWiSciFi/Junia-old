#pragma once

#include <Junia/Renderer/RenderContext.hpp>
#include <Junia/Window.hpp>

namespace Junia
{
	class VulkanRenderContext : public RenderContext
	{
	public:
		VulkanRenderContext(Window* window);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	};
}
