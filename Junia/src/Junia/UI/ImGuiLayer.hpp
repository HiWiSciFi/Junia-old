#pragma once

#include <Junia/Layer.hpp>
#include <glm/vec4.hpp>

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
		bool show_another_window = false;
	};
}
