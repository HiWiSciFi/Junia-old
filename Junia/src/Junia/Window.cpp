#include "GlfwWindow.hpp"

namespace Junia
{
	Window* Window::Create()
	{
#ifdef JE_TARGETPLATFORM_WINDOW
		return new GlfwWindow();
#endif
		return nullptr;
	}

}
