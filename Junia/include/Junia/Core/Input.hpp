#pragma once
#include <utility>

namespace Junia
{
	class Input
	{
	public:
		static bool IsKeyDown(const int keycode, uint32_t window = 0);
		static bool IsMouseButtonDown(const int button, uint32_t window = 0);
		static std::pair<int, int> GetMousePosition(uint32_t window = 0);

		static inline bool IsKeyUp(const int keycode, uint32_t window = 0) { return !IsKeyDown(window, keycode); }
		static inline bool IsMouseButtonUp(const int button, uint32_t window = 0) { return !IsMouseButtonDown(window, button); }
		static inline int GetMouseX(uint32_t window = 0) { return GetMousePosition(window).first;  }
		static inline int GetMouseY(uint32_t window = 0) { return GetMousePosition(window).second; }
	};
}
