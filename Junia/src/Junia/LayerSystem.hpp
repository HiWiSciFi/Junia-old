#pragma once
#include "Layer.hpp"
#include <functional>
#include <deque>

namespace Junia
{
	class LayerSystem
	{
	public:
		LayerSystem();
		LayerSystem(const LayerSystem& obj) = default;
		LayerSystem& operator=(const LayerSystem&) = default;
		LayerSystem& operator=(LayerSystem&&) = default;
		virtual ~LayerSystem();

		Layer* PushLayerFront(Layer* layer);
		Layer* PushLayerBack(Layer* layer);
		Layer* PopLayerFront();
		Layer* PopLayerBack();

		void IterateForward(std::function<void(Layer* const layer)>);
		void IterateBackward(std::function<void(Layer* const layer)>);

	private:
		std::deque<Layer*> layerStack;
	};
}
