#ifdef JE_TARGETPLATFORM_WINDOWS

#include "WindowsInput.hpp"
#include <Windows.h>
#include <Junia/Core/KeyCodes.hpp>
#include <Junia/Core/MouseButtonCodes.hpp>
#include <Junia/Core/Log.hpp>

namespace Junia
{
	Input* Input::instance = new WindowsInput();

	unsigned char WindowsInput::JeToWinKey[256] = { };
	unsigned char WindowsInput::WinToJeKey[256] = { };
	unsigned char WindowsInput::WinToJeButton[8] = { };
	unsigned char WindowsInput::JeToWinButton[8] = { };


	void WindowsInput::PopulateConversionArrays()
	{
		JeToWinKey[JE_KEY_HOME] = VK_HOME;
		JeToWinKey[JE_KEY_END] = VK_END;
		JeToWinKey[JE_KEY_PRINT_SCREEN] = VK_SNAPSHOT;
		JeToWinKey[JE_KEY_NUM_LOCK] = VK_NUMLOCK;
		JeToWinKey[JE_KEY_CAPS_LOCK] = VK_CAPITAL;
		JeToWinKey[JE_KEY_SCROLL_LOCK] = VK_SCROLL;
		JeToWinKey[JE_KEY_BACKSPACE] = VK_BACK;
		JeToWinKey[JE_KEY_TAB] = VK_TAB;
		JeToWinKey[JE_KEY_ENTER] = VK_RETURN;
		JeToWinKey[JE_KEY_MENU] = VK_EXSEL;
		JeToWinKey[JE_KEY_PAGE_UP] = VK_PRIOR;
		JeToWinKey[JE_KEY_PAGE_DOWN] = VK_NEXT;
		JeToWinKey[JE_KEY_PAUSE] = VK_PAUSE;
		JeToWinKey[JE_KEY_INSERT] = VK_INSERT;
		JeToWinKey[JE_KEY_ESCAPE] = VK_ESCAPE;
		JeToWinKey[JE_KEY_SPACE] = VK_SPACE;
		JeToWinKey[JE_KEY_APOSTROPHE] = VK_OEM_7;
		JeToWinKey[JE_KEY_COMMA] = VK_OEM_COMMA;
		JeToWinKey[JE_KEY_MINUS] = VK_OEM_MINUS;
		JeToWinKey[JE_KEY_PERIOD] = VK_OEM_PERIOD;
		JeToWinKey[JE_KEY_SLASH] = VK_OEM_2;
		JeToWinKey[JE_KEY_0] = 0x30;
		JeToWinKey[JE_KEY_1] = 0x31;
		JeToWinKey[JE_KEY_2] = 0x32;
		JeToWinKey[JE_KEY_3] = 0x33;
		JeToWinKey[JE_KEY_4] = 0x34;
		JeToWinKey[JE_KEY_5] = 0x35;
		JeToWinKey[JE_KEY_6] = 0x36;
		JeToWinKey[JE_KEY_7] = 0x37;
		JeToWinKey[JE_KEY_8] = 0x38;
		JeToWinKey[JE_KEY_9] = 0x39;
		JeToWinKey[JE_KEY_SEMICOLON] = VK_OEM_1;
		JeToWinKey[JE_KEY_EQUAL] = VK_OEM_PLUS;
		JeToWinKey[JE_KEY_A] = 0x41;
		JeToWinKey[JE_KEY_B] = 0x42;
		JeToWinKey[JE_KEY_C] = 0x43;
		JeToWinKey[JE_KEY_D] = 0x44;
		JeToWinKey[JE_KEY_E] = 0x45;
		JeToWinKey[JE_KEY_F] = 0x46;
		JeToWinKey[JE_KEY_G] = 0x47;
		JeToWinKey[JE_KEY_H] = 0x48;
		JeToWinKey[JE_KEY_I] = 0x49;
		JeToWinKey[JE_KEY_J] = 0x4A;
		JeToWinKey[JE_KEY_K] = 0x4B;
		JeToWinKey[JE_KEY_L] = 0x4C;
		JeToWinKey[JE_KEY_M] = 0x4D;
		JeToWinKey[JE_KEY_N] = 0x4E;
		JeToWinKey[JE_KEY_O] = 0x4F;
		JeToWinKey[JE_KEY_P] = 0x50;
		JeToWinKey[JE_KEY_Q] = 0x51;
		JeToWinKey[JE_KEY_R] = 0x52;
		JeToWinKey[JE_KEY_S] = 0x53;
		JeToWinKey[JE_KEY_T] = 0x54;
		JeToWinKey[JE_KEY_U] = 0x55;
		JeToWinKey[JE_KEY_V] = 0x56;
		JeToWinKey[JE_KEY_W] = 0x57;
		JeToWinKey[JE_KEY_X] = 0x58;
		JeToWinKey[JE_KEY_Y] = 0x59;
		JeToWinKey[JE_KEY_Z] = 0x5A;
		JeToWinKey[JE_KEY_LEFT_BRACKET] = VK_OEM_4;
		JeToWinKey[JE_KEY_BACKSLASH] = VK_OEM_5;
		JeToWinKey[JE_KEY_RIGHT_BRACKET] = VK_OEM_6;
		//JeToWinKey[JE_KEY_GRAVE_ACCENT] = VK_;
		JeToWinKey[JE_KEY_LEFT] = VK_LEFT;
		JeToWinKey[JE_KEY_UP] = VK_UP;
		JeToWinKey[JE_KEY_RIGHT] = VK_RIGHT;
		JeToWinKey[JE_KEY_DOWN] = VK_DOWN;
		JeToWinKey[JE_KEY_F1] = VK_F1;
		JeToWinKey[JE_KEY_F2] = VK_F2;
		JeToWinKey[JE_KEY_F3] = VK_F3;
		JeToWinKey[JE_KEY_F4] = VK_F4;
		JeToWinKey[JE_KEY_F5] = VK_F5;
		JeToWinKey[JE_KEY_F6] = VK_F6;
		JeToWinKey[JE_KEY_F7] = VK_F7;
		JeToWinKey[JE_KEY_F8] = VK_F8;
		JeToWinKey[JE_KEY_F9] = VK_F9;
		JeToWinKey[JE_KEY_F10] = VK_F10;
		JeToWinKey[JE_KEY_F11] = VK_F11;
		JeToWinKey[JE_KEY_F12] = VK_F12;
		JeToWinKey[JE_KEY_F13] = VK_F13;
		JeToWinKey[JE_KEY_F14] = VK_F14;
		JeToWinKey[JE_KEY_F15] = VK_F15;
		JeToWinKey[JE_KEY_F16] = VK_F16;
		JeToWinKey[JE_KEY_F17] = VK_F17;
		JeToWinKey[JE_KEY_F18] = VK_F18;
		JeToWinKey[JE_KEY_F19] = VK_F19;
		JeToWinKey[JE_KEY_F20] = VK_F20;
		JeToWinKey[JE_KEY_F21] = VK_F21;
		JeToWinKey[JE_KEY_F22] = VK_F22;
		JeToWinKey[JE_KEY_F23] = VK_F23;
		JeToWinKey[JE_KEY_F24] = VK_F24;
		JeToWinKey[JE_KEY_DELETE] = VK_DELETE;
		JeToWinKey[JE_KEY_LEFT_SHIFT] = VK_LSHIFT;
		JeToWinKey[JE_KEY_RIGHT_SHIFT] = VK_RSHIFT;
		JeToWinKey[JE_KEY_LEFT_CONTROL] = VK_LCONTROL;
		JeToWinKey[JE_KEY_RIGHT_CONTROL] = VK_RCONTROL;
		JeToWinKey[JE_KEY_LEFT_ALT] = VK_LMENU;
		JeToWinKey[JE_KEY_RIGHT_ALT] = VK_RMENU;
		JeToWinKey[JE_KEY_LEFT_SUPER] = VK_LWIN;
		JeToWinKey[JE_KEY_RIGHT_SUPER] = VK_RWIN;
		//JeToWinKey[JE_KEY_KP_ENTER] = VK_RETURN; // WRONG
		JeToWinKey[JE_KEY_KP_MULTIPLY] = VK_MULTIPLY;
		JeToWinKey[JE_KEY_KP_ADD] = VK_ADD;
		JeToWinKey[JE_KEY_KP_SUBTRACT] = VK_SUBTRACT;
		JeToWinKey[JE_KEY_KP_DECIMAL] = VK_DECIMAL;
		JeToWinKey[JE_KEY_KP_DIVIDE] = VK_DIVIDE;
		JeToWinKey[JE_KEY_KP_0] = VK_NUMPAD0;
		JeToWinKey[JE_KEY_KP_1] = VK_NUMPAD1;
		JeToWinKey[JE_KEY_KP_2] = VK_NUMPAD2;
		JeToWinKey[JE_KEY_KP_3] = VK_NUMPAD3;
		JeToWinKey[JE_KEY_KP_4] = VK_NUMPAD4;
		JeToWinKey[JE_KEY_KP_5] = VK_NUMPAD5;
		JeToWinKey[JE_KEY_KP_6] = VK_NUMPAD6;
		JeToWinKey[JE_KEY_KP_7] = VK_NUMPAD7;
		JeToWinKey[JE_KEY_KP_8] = VK_NUMPAD8;
		JeToWinKey[JE_KEY_KP_9] = VK_NUMPAD9;
		JeToWinKey[JE_KEY_KP_EQUAL] = VK_OEM_PLUS;

		WinToJeKey[VK_HOME] = JE_KEY_HOME;
		WinToJeKey[VK_END] = JE_KEY_END;
		WinToJeKey[VK_SNAPSHOT] = JE_KEY_PRINT_SCREEN;
		WinToJeKey[VK_NUMLOCK] = JE_KEY_NUM_LOCK;
		WinToJeKey[VK_CAPITAL] = JE_KEY_CAPS_LOCK;
		WinToJeKey[VK_SCROLL] = JE_KEY_SCROLL_LOCK;
		WinToJeKey[VK_BACK] = JE_KEY_BACKSPACE;
		WinToJeKey[VK_TAB] = JE_KEY_TAB;
		WinToJeKey[VK_RETURN] = JE_KEY_ENTER;
		WinToJeKey[VK_EXSEL] = JE_KEY_MENU;
		WinToJeKey[VK_PRIOR] = JE_KEY_PAGE_UP;
		WinToJeKey[VK_NEXT] = JE_KEY_PAGE_DOWN;
		WinToJeKey[VK_PAUSE] = JE_KEY_PAUSE;
		WinToJeKey[VK_INSERT] = JE_KEY_INSERT;
		WinToJeKey[VK_ESCAPE] = JE_KEY_ESCAPE;
		WinToJeKey[VK_SPACE] = JE_KEY_SPACE;
		WinToJeKey[VK_OEM_7] = JE_KEY_APOSTROPHE;
		WinToJeKey[VK_OEM_COMMA] = JE_KEY_COMMA;
		WinToJeKey[VK_OEM_MINUS] = JE_KEY_MINUS;
		WinToJeKey[VK_OEM_PERIOD] = JE_KEY_PERIOD;
		WinToJeKey[VK_OEM_2] = JE_KEY_SLASH;
		WinToJeKey[0x30] = JE_KEY_0;
		WinToJeKey[0x31] = JE_KEY_1;
		WinToJeKey[0x32] = JE_KEY_2;
		WinToJeKey[0x33] = JE_KEY_3;
		WinToJeKey[0x34] = JE_KEY_4;
		WinToJeKey[0x35] = JE_KEY_5;
		WinToJeKey[0x36] = JE_KEY_6;
		WinToJeKey[0x37] = JE_KEY_7;
		WinToJeKey[0x38] = JE_KEY_8;
		WinToJeKey[0x39] = JE_KEY_9;
		WinToJeKey[VK_OEM_1] = JE_KEY_SEMICOLON;
		WinToJeKey[VK_OEM_PLUS] = JE_KEY_EQUAL;
		WinToJeKey[0x41] = JE_KEY_A;
		WinToJeKey[0x42] = JE_KEY_B;
		WinToJeKey[0x43] = JE_KEY_C;
		WinToJeKey[0x44] = JE_KEY_D;
		WinToJeKey[0x45] = JE_KEY_E;
		WinToJeKey[0x46] = JE_KEY_F;
		WinToJeKey[0x47] = JE_KEY_G;
		WinToJeKey[0x48] = JE_KEY_H;
		WinToJeKey[0x49] = JE_KEY_I;
		WinToJeKey[0x4A] = JE_KEY_J;
		WinToJeKey[0x4B] = JE_KEY_K;
		WinToJeKey[0x4C] = JE_KEY_L;
		WinToJeKey[0x4D] = JE_KEY_M;
		WinToJeKey[0x4E] = JE_KEY_N;
		WinToJeKey[0x4F] = JE_KEY_O;
		WinToJeKey[0x50] = JE_KEY_P;
		WinToJeKey[0x51] = JE_KEY_Q;
		WinToJeKey[0x52] = JE_KEY_R;
		WinToJeKey[0x53] = JE_KEY_S;
		WinToJeKey[0x54] = JE_KEY_T;
		WinToJeKey[0x55] = JE_KEY_U;
		WinToJeKey[0x56] = JE_KEY_V;
		WinToJeKey[0x57] = JE_KEY_W;
		WinToJeKey[0x58] = JE_KEY_X;
		WinToJeKey[0x59] = JE_KEY_Y;
		WinToJeKey[0x5A] = JE_KEY_Z;
		WinToJeKey[VK_OEM_4] = JE_KEY_LEFT_BRACKET;
		WinToJeKey[VK_OEM_5] = JE_KEY_BACKSLASH;
		WinToJeKey[VK_OEM_6] = JE_KEY_RIGHT_BRACKET;
		//WinToJeKey[VK_] = JE_KEY_GRAVE_ACCENT;
		WinToJeKey[VK_LEFT] = JE_KEY_LEFT;
		WinToJeKey[VK_UP] = JE_KEY_UP;
		WinToJeKey[VK_RIGHT] = JE_KEY_RIGHT;
		WinToJeKey[VK_DOWN] = JE_KEY_DOWN;
		WinToJeKey[VK_F1] = JE_KEY_F1;
		WinToJeKey[VK_F2] = JE_KEY_F2;
		WinToJeKey[VK_F3] = JE_KEY_F3;
		WinToJeKey[VK_F4] = JE_KEY_F4;
		WinToJeKey[VK_F5] = JE_KEY_F5;
		WinToJeKey[VK_F6] = JE_KEY_F6;
		WinToJeKey[VK_F7] = JE_KEY_F7;
		WinToJeKey[VK_F8] = JE_KEY_F8;
		WinToJeKey[VK_F9] = JE_KEY_F9;
		WinToJeKey[VK_F10] = JE_KEY_F10;
		WinToJeKey[VK_F11] = JE_KEY_F11;
		WinToJeKey[VK_F12] = JE_KEY_F12;
		WinToJeKey[VK_F13] = JE_KEY_F13;
		WinToJeKey[VK_F14] = JE_KEY_F14;
		WinToJeKey[VK_F15] = JE_KEY_F15;
		WinToJeKey[VK_F16] = JE_KEY_F16;
		WinToJeKey[VK_F17] = JE_KEY_F17;
		WinToJeKey[VK_F18] = JE_KEY_F18;
		WinToJeKey[VK_F19] = JE_KEY_F19;
		WinToJeKey[VK_F20] = JE_KEY_F20;
		WinToJeKey[VK_F21] = JE_KEY_F21;
		WinToJeKey[VK_F22] = JE_KEY_F22;
		WinToJeKey[VK_F23] = JE_KEY_F23;
		WinToJeKey[VK_F24] = JE_KEY_F24;
		WinToJeKey[VK_DELETE] = JE_KEY_DELETE;
		WinToJeKey[VK_LSHIFT] = JE_KEY_LEFT_SHIFT;
		WinToJeKey[VK_RSHIFT] = JE_KEY_RIGHT_SHIFT;
		WinToJeKey[VK_LCONTROL] = JE_KEY_LEFT_CONTROL;
		WinToJeKey[VK_RCONTROL] = JE_KEY_RIGHT_CONTROL;
		WinToJeKey[VK_LMENU] = JE_KEY_LEFT_ALT;
		WinToJeKey[VK_RMENU] = JE_KEY_RIGHT_ALT;
		WinToJeKey[VK_LWIN] = JE_KEY_LEFT_SUPER;
		WinToJeKey[VK_RWIN] = JE_KEY_RIGHT_SUPER;
		//WinToJeKey[VK_RETURN] = JE_KEY_KP_ENTER; // WRONG
		WinToJeKey[VK_MULTIPLY] = JE_KEY_KP_MULTIPLY;
		WinToJeKey[VK_ADD] = JE_KEY_KP_ADD;
		WinToJeKey[VK_SUBTRACT] = JE_KEY_KP_SUBTRACT;
		WinToJeKey[VK_DECIMAL] = JE_KEY_KP_DECIMAL;
		WinToJeKey[VK_DIVIDE] = JE_KEY_KP_DIVIDE;
		WinToJeKey[VK_NUMPAD0] = JE_KEY_KP_0;
		WinToJeKey[VK_NUMPAD1] = JE_KEY_KP_1;
		WinToJeKey[VK_NUMPAD2] = JE_KEY_KP_2;
		WinToJeKey[VK_NUMPAD3] = JE_KEY_KP_3;
		WinToJeKey[VK_NUMPAD4] = JE_KEY_KP_4;
		WinToJeKey[VK_NUMPAD5] = JE_KEY_KP_5;
		WinToJeKey[VK_NUMPAD6] = JE_KEY_KP_6;
		WinToJeKey[VK_NUMPAD7] = JE_KEY_KP_7;
		WinToJeKey[VK_NUMPAD8] = JE_KEY_KP_8;
		WinToJeKey[VK_NUMPAD9] = JE_KEY_KP_9;
		//WinToJeKey[VK_OEM_PLUS] = JE_KEY_KP_EQUAL; // WRONG


		JeToWinButton[JE_MOUSEBUTTON_LEFT]   = VK_LBUTTON;
		JeToWinButton[JE_MOUSEBUTTON_MIDDLE] = VK_MBUTTON;
		JeToWinButton[JE_MOUSEBUTTON_RIGHT]  = VK_RBUTTON;

		WinToJeButton[VK_LBUTTON] =   JE_MOUSEBUTTON_LEFT;
		WinToJeButton[VK_MBUTTON] = JE_MOUSEBUTTON_MIDDLE;
		WinToJeButton[VK_RBUTTON] =  JE_MOUSEBUTTON_RIGHT;
	}

	bool WindowsInput::IsKeyDownImplementation(int keycode)
	{
		return GetKeyState(JeToWinKey[keycode]) & 0x8000;
	}

	bool WindowsInput::IsMouseButtonDownImplementation(int button)
	{
		return GetKeyState(JeToWinButton[button]) & 0x8000;
	}

	std::pair<int, int> WindowsInput::GetMousePositionImplementation()
	{
		POINT pos;
		GetCursorPos(&pos);
		return std::pair<int, int>(static_cast<int>(pos.x), static_cast<int>(pos.y));
	}
}

#endif
