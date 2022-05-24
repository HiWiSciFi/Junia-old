#include "LayerSystem.hpp"

namespace Junia
{
	LayerSystem::LayerSystem() = default;

	LayerSystem::~LayerSystem()
	{
		for (const Layer* layer : layerStack) delete layer;
	}

	Layer* LayerSystem::PushLayerFront(Layer* layer)
	{
		layerStack.push_front(layer);
		layer->OnEnable();
		return layerStack.front();
	}

	Layer* LayerSystem::PushLayerBack(Layer* layer)
	{
		layerStack.push_back(layer);
		layer->OnEnable();
		return layerStack.back();
	}

	Layer* LayerSystem::PopLayerFront()
	{
		layerStack.front()->OnDisable();
		Layer* tmp = layerStack.front();
		layerStack.pop_front();
		return tmp;
	}

	Layer* LayerSystem::PopLayerBack()
	{
		layerStack.back()->OnDisable();
		Layer* tmp = layerStack.back();
		layerStack.pop_back();
		return tmp;
	}

	void LayerSystem::IterateForward(std::function<void(Layer* const layer)> handler)
	{
		for (int i = layerStack.size()-1; i >= 0; i--) handler(layerStack[i]);
	}

	void LayerSystem::IterateBackward(std::function<void(Layer* const layer)> handler)
	{
		for (int i = 0; i < layerStack.size(); i++) handler(layerStack[i]);
	}
}
