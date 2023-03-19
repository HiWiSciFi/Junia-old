#pragma once

#include <cstdint>

namespace Junia
{
	/**
	 * @brief Initializes the timer functionality
	*/
	void InitTimer();

	/**
	 * @brief Get the current time on the timer
	 * @return The time currently on the timer
	*/
	uint64_t GetTimerTime();

	/**
	 * @brief Get the frequency of the timer
	 * @return The frequency of the timer
	*/
	uint64_t GetTimerFrequency();
}
