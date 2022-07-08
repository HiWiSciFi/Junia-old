#pragma once

#if JE_WINDOWAPI == JE_WINDOWAPI_WIN32

#include <Junia/Core/Input.hpp>

namespace Junia
{
	class WindowsInput : public Input
	{
	public:
		static unsigned char WinToJeKey[256];
		static unsigned char JeToWinKey[256];
		static unsigned char WinToJeButton[8];
		static unsigned char JeToWinButton[8];
		static void PopulateConversionArrays();

	protected:
		bool IsKeyDownImplementation(int keycode) override;
		bool IsMouseButtonDownImplementation(int button) override;
		std::pair<int, int> GetMousePositionImplementation() override;
	};
}
#endif
