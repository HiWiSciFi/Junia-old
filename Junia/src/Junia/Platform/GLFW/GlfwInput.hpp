#pragma once

#ifdef JE_TARGETPLATFORM_GLFW

#include <Junia/Core/Input.hpp>

namespace Junia
{
	class GlfwInput : public Input
	{
	protected:
		bool IsKeyDownImplementation(int keycode) override;
		bool IsMouseButtonDownImplementation(int button) override;
		std::pair<int, int> GetMousePositionImplementation() override;
	};
}

#endif
