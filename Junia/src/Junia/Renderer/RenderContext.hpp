#pragma once

namespace Junia
{
	class RenderContext
	{
	public:
		virtual void Init() = 0;
		virtual void ContextSwapBuffers() = 0;
	};
}
