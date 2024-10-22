#include <Junia/Core/Time.hpp>

#ifdef _WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#undef WIN32_LEAN_AND_MEAN
#undef ERROR
#undef IGNORE

namespace Junia {

static LARGE_INTEGER frequency{ };

void InitTimer() {
	QueryPerformanceFrequency(&frequency);
}

std::uint64_t GetTimerTime() {
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return static_cast<std::uint64_t>(time.QuadPart);
}

std::uint64_t GetTimerFrequency() {
	return static_cast<std::uint64_t>(frequency.QuadPart);
}

} // namespace Junia

#endif
