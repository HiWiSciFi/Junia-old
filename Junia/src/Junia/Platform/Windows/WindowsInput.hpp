#pragma once

#include <Junia/Input.hpp>

namespace Junia
{
	class WindowsInput : public Input
	{
	protected:
		bool IsKeyDownImplementation(int keycode) override;
		bool IsMouseButtonDownImplementation(int button) override;
		std::pair<float, float> GetMousePositionImplementation() override;
	};
}
