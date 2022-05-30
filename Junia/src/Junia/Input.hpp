#pragma once

namespace Junia
{
	class Input
	{
	public:
		static bool IsKeyDown(int keycode) { return instance->IsKeyDownImplementation(keycode); }
		static bool IsKeyUp(int keycode) { return !IsKeyDown(keycode); }
	protected:
		virtual bool IsKeyDownImplementation(int keycode) = 0;
	private:
		static Input* instance;
	};
}
