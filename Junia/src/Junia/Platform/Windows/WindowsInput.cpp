#ifdef JE_TARGETPLATFORM_WINDOWS

#include "WindowsInput.hpp"
#include <Windows.h>
#include <Junia/KeyCodes.hpp>
#include <Junia/MouseButtonCodes.hpp>
#include <Junia/Log.hpp>

namespace Junia
{
	Input* Input::instance = new WindowsInput();

	int JeToWinKey(int keycode)
	{
		switch (keycode)
		{
			case JE_KEY_LEFT:  return  VK_LEFT;
			case JE_KEY_UP:    return    VK_UP;
			case JE_KEY_RIGHT: return VK_RIGHT;
			case JE_KEY_DOWN:  return  VK_DOWN;
			case JE_MOUSEBUTTON_LEFT:  return VK_LBUTTON;
			case JE_MOUSEBUTTON_RIGHT: return VK_RBUTTON;
			default: return keycode;
		}
	}

	bool WindowsInput::IsKeyDownImplementation(int keycode)
	{
		return GetKeyState(JeToWinKey(keycode)) & 0x8000;
	}

	bool WindowsInput::IsMouseButtonDownImplementation(int button)
	{
		return GetKeyState(JeToWinKey(button)) & 0x8000;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImplementation()
	{
		return std::pair<float, float>();
	}
}

#endif
