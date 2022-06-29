#ifdef JE_TARGETPLATFORM_WINDOWS

#include "../Platform.hpp"

#include <Windows.h>

namespace Junia
{
	float Junia::Platform::GetTime()
	{
		unsigned long timems = timeGetTime();
		return timems / 1000.0f;
	}
}

#endif
