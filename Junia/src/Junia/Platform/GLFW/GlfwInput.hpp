#pragma once

#if JE_WINDOWAPI == JE_WINDOWAPI_GLFW

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
