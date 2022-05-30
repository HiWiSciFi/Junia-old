#pragma once

#include <Junia/Input.hpp>

namespace Junia
{
	class GlfwInput : public Input
	{
	protected:
		virtual bool IsKeyDownImplementation(int keycode) override;
	};
}
