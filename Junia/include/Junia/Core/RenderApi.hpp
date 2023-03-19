#pragma once

#include <cstdint>

namespace Junia
{
	/**
	 * @brief The render APIs that can be used to render scenes
	*/
	enum class RenderApi : uint8_t
	{
		NONE = 0,
		VULKAN = 1
	};
}
