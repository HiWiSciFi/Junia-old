#include <Junia/Core/Time.hpp>

#ifdef __linux__

#include <time.h>

namespace Junia {

static std::uint64_t frequency = 0;

void InitTimer() {
	frequency = 1000000000;
}

std::uint64_t GetTimerTime() {
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (static_cast<std::uint64_t>(ts.tv_sec) * frequency) + static_cast<std::uint64_t>(ts.tv_nsec);
}

std::uint64_t GetTimerFrequency() {
	return frequency;
}

} // namespace Junia

#endif
