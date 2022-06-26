#ifdef JE_TARGETPLATFORM_WINDOWS

#include "../Platform.hpp"

#include <Windows.h>

namespace Junia
{
	float Junia::Platform::GetTime()
	{
		FILETIME ft_now;
		GetSystemTimeAsFileTime(&ft_now);
		long long ll_now;
		static long long ll_start = (LONGLONG)ft_now.dwLowDateTime + ((LONGLONG)(ft_now.dwHighDateTime) << 32LL);
		ll_now = (LONGLONG)ft_now.dwLowDateTime + ((LONGLONG)(ft_now.dwHighDateTime) << 32LL);
		return (ll_now - ll_start) / 1000.0f;
	}
}
#endif
