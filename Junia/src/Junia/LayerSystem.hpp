#pragma once
#include <deque>

#include "Base.hpp"
#include "Layer.hpp"

namespace Junia
{
	class JE_API_IO LayerSystem
	{
	public:
		LayerSystem();
		LayerSystem(const LayerSystem& obj) = default;
		LayerSystem& operator=(const LayerSystem&) = default;
		LayerSystem& operator=(LayerSystem&&) = default;
		virtual ~LayerSystem();

		void PushLayer(Layer* layer);
		void PopLayer();

	private:
		std::deque<Layer*> layerStack;
	};
}
