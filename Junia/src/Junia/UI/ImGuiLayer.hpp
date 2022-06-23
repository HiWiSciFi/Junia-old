#pragma once

#include <Junia/Layer.hpp>
#include <Junia/Events/MouseEvents.hpp>
#include <Junia/Events/KeyboardEvents.hpp>
#include <Junia/Events/WindowEvents.hpp>

namespace Junia
{
	class ImGuiLayer : public Layer
	{
	public:
		void OnEnable() override;
		void OnUpdate() override;
		void OnDisable() override;

	private:
		bool show_demo_window = true;
	};
}
