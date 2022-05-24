#include "LayerSystem.hpp"

namespace Junia
{
	LayerSystem::LayerSystem() = default;

	LayerSystem::~LayerSystem()
	{
		for (const Layer* layer : layerStack) delete layer;
	}

	void LayerSystem::PushLayer(Layer* layer)
	{
		layerStack.push_back(layer);
	}

	void LayerSystem::PopLayer()
	{
		layerStack.pop_back();
	}
}
