#pragma once

#include <Junia/Layer.hpp>

namespace Junia
{
	class JUILayer : public Layer
	{
	public:
		void OnEnable() override;
		void OnUpdate() override;
		void OnDisable() override;

	private:
		bool show_demo_window = true;
	};
}
