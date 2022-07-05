#pragma once

#include <Junia/Renderer/RenderContext.hpp>
#include <Junia/Core/Window.hpp>

namespace Junia
{
	class VulkanRenderContext : public RenderContext
	{
	public:
		explicit VulkanRenderContext(Window* window);

		virtual void Init() override;
		virtual void ContextSwapBuffers() override;
	};
}
