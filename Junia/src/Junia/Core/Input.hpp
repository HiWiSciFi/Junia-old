#pragma once
#include <utility>
#include <Junia/Core/KeyCodes.hpp>
#include <Junia/Core/MouseButtonCodes.hpp>

namespace Junia
{
	class Input
	{
	public:
		virtual ~Input() = default;
		static bool IsKeyDown(const int keycode) { return instance->IsKeyDownImplementation(keycode); }
		static bool IsKeyUp(const int keycode) { return !IsKeyDown(keycode); }
		static bool IsMouseButtonDown(const int button) { return instance->IsMouseButtonDownImplementation(button); }
		static bool IsMouseButtonUp(const int button) { return !IsMouseButtonDown(button); }
		static int GetMouseX() { return GetMousePosition().first; }
		static int GetMouseY() { return GetMousePosition().second; }
		static std::pair<int, int> GetMousePosition() { return instance->GetMousePositionImplementation(); }
	protected:
		virtual bool IsKeyDownImplementation(int keycode) = 0;
		virtual bool IsMouseButtonDownImplementation(int button) = 0;
		virtual std::pair<int, int> GetMousePositionImplementation() = 0;
	private:
		static Input* instance;
	};
}
