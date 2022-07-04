#pragma once

#include <Junia/Input.hpp>

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
