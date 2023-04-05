#pragma once

#include "../Core/WindowApi.hpp"
#include "../Core/RenderApi.hpp"

namespace Junia
{
	class Window;

	/**
	 * @brief A wrapper for RenderAPI Surfaces to render to
	*/
	class Surface
	{
	public:
		/**
		 * @brief Create a new Surface from a window
		 * @param window a pointer the window this surface will be created for
		 * @param windowApi The window api that was used to create the window
		 *                  handle
		 * @param renderApi The render api to create a surface for
		 * @return a pointer to the created window
		*/
		static Surface* Create(Window* window, WindowApi windowApi, RenderApi renderApi);

		virtual ~Surface() = 0;

		/**
		 * @brief Call when the framebuffer has been resized so that the surface
		 *        etc. can be updated (optional, in case the resize is not
		 *        triggered automatically)
		*/
		virtual void FramebufferResized() = 0;

		/**
		 * @brief Draw a test triangle TODO: replace with proper API
		*/
		virtual void Draw() = 0;
	};
} // namespace Junia
