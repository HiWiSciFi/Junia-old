#pragma once
#include <Junia/Core/Layer.hpp>

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
		~LayerSystem();

		Layer* PushLayerFront(Layer* layer);
		Layer* PushLayerBack(Layer* layer);
		Layer* PopLayerFront();
		Layer* PopLayerBack();

		void IterateForward(const std::function<void(Layer* const layer)>&) const;
		void IterateBackward(const std::function<void(Layer* const layer)>&) const;

	private:
		std::deque<Layer*> layerStack;
	};
}
