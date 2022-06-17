#include "WindowsInput.hpp"

namespace Junia
{
#ifdef JE_TARGETPLATFORM_WINDOWS
	//Input* Input::instance = new WindowsInput();
#endif

	bool WindowsInput::IsKeyDownImplementation(int keycode)
	{
		return false;
	}

	bool WindowsInput::IsMouseButtonDownImplementation(int button)
	{
		return false;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImplementation()
	{
		return std::pair<float, float>();
	}
}
