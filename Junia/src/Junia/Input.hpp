#pragma once
#include <utility>

namespace Junia
{
	class Input
	{
	public:
		static bool IsKeyDown(const int keycode) { return instance->IsKeyDownImplementation(keycode); }
		static bool IsKeyUp(const int keycode) { return !IsKeyDown(keycode); }
		static bool IsMouseButtonDown(const int button) { return instance->IsMouseButtonDownImplementation(button); }
		static bool IsMouseButtonUp(const int button) { return !IsMouseButtonDown(button); }
		static float GetMouseX() { return GetMousePosition().first; }
		static float GetMouseY() { return GetMousePosition().second; }
		static std::pair<float, float> GetMousePosition() { return instance->GetMousePositionImplementation(); }
	protected:
		virtual bool IsKeyDownImplementation(int keycode) = 0;
		virtual bool IsMouseButtonDownImplementation(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImplementation() = 0;
	private:
		static Input* instance;
	};
}
