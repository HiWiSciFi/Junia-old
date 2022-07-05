#pragma once

namespace Junia
{
	class RenderContext
	{
	public:
		virtual ~RenderContext() = default;
		virtual void Init() = 0;
		virtual void ContextSwapBuffers() = 0;
	};
}
