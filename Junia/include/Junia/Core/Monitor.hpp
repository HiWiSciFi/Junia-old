#pragma once

#include "../../JMath/Vector2.hpp"
#include "../../JMath/Vector3.hpp"
#include <cstdint>
#include <string>

namespace Junia
{
	/**
	 * @brief A wrapper for monitors that can be used to render on
	*/
	class Monitor
	{
	public:
		virtual ~Monitor() = 0;

		/**
		 * @brief Get the name of the monitor
		 * @return The identifier of the monitor (prepended with "<index>: " to
		 *         make monitor names unique)
		*/
		virtual const std::string& GetName() const = 0;

		/**
		 * @brief Get the position of the monitor on the virtual screen (primary
		 *        monitor is at (0,0))
		 * @return A Vector containing the coordinates of the monitor
		*/
		virtual JMath::uiVec2 GetPosition() const = 0;

		/**
		 * @brief Get the resolution of the monitor
		 * @return A Vector containing the resolution of the monitor
		*/
		virtual JMath::uiVec2 GetResolution() const = 0;

		/**
		 * @brief Get the colordepth of the red green and blue channels
		 * @return A Vector containing the bitdepths of the color channels
		*/
		virtual JMath::uiVec3 GetColorBits() const = 0;

		/**
		 * @brief Get the refresh rate of the monitor
		 * @return An unsigned integer containing the rounded refresh rate
		*/
		virtual uint32_t GetRefreshRate() const = 0;

		/**
		 * @brief Get the WindowAPI native handle of the monitor
		 * @return A handle to the monitor
		*/
		virtual void* GetNative() const = 0;

		/**
		 * @brief Get all available monitors
		 * @return A pointer to the start of an array of monitors (see
		 *         Junia::Monitor::GetMonitorCount() for the array length) where
		 *         the first element is the primary monitor
		*/
		static Monitor** GetAll();

		/**
		 * @brief Get the amount of connected monitors
		 * @return The amount of monitors
		*/
		static size_t GetMonitorCount();

		/**
		 * @brief Get the primary monitor
		 * @return A pointer to the primary monitor
		*/
		static Monitor* GetPrimary();
	};
}
