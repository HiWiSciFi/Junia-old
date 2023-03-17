#pragma once

#include "../Core/WindowApi.hpp"
#include "../Core/RenderApi.hpp"

namespace Junia
{
	class Surface
	{
	public:
		static Surface* Create(void* window, WindowApi windowApi, RenderApi renderApi);

		virtual ~Surface() = 0;
		virtual void FramebufferResized() = 0;
		virtual void Draw() = 0;
	};
}
