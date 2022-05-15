#pragma once
#include "Base.hpp"

namespace Junia
{
	class JE_API_IO Window
	{
	public:
		static Window* Create();

	protected:
		Window() = default;
		~Window() = default;
	};
}
