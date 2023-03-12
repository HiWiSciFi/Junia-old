#include <Junia/Core/Time.hpp>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

namespace Junia
{
	static uint64_t frequency = 10000; // TODO: QueryPerformanceFrequency(&frequency);

	uint64_t GetTimerTime()
	{
		uint64_t time;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&time));
		return time;
	}

	uint64_t GetTimerFrequency()
	{
		return frequency;
	}
}

#endif
