#pragma once

#include <cstdint>

namespace Junia
{
	/**
	 * @brief The window apis that can be used to create and interact with
	 *        windows
	*/
	enum class WindowApi : uint8_t
	{
		NONE = 0,
		GLFW = 1
	};
} // namespace Junia
