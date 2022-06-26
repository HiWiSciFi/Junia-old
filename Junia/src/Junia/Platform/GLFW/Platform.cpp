#ifdef JE_TARGETPLATFORM_GLFW

#include "../Platform.hpp"

#include <GLFW/glfw3.h>

namespace Junia
{
	float Junia::Platform::GetTime()
	{
		return static_cast<float>(glfwGetTime());
	}
}
#endif
