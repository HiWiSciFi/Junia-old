#include "LayerSystem.hpp"

namespace Junia
{
	LayerSystem::LayerSystem() = default;

	LayerSystem::~LayerSystem()
	{
		Layer* layer;
		while ((layer = PopLayerFront()) != nullptr) delete layer;
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
		if (layerStack.empty()) return nullptr;
		layerStack.front()->OnDisable();
		Layer* tmp = layerStack.front();
		layerStack.pop_front();
		return tmp;
	}

	Layer* LayerSystem::PopLayerBack()
	{
		if (layerStack.empty()) return nullptr;
		layerStack.back()->OnDisable();
		Layer* tmp = layerStack.back();
		layerStack.pop_back();
		return tmp;
	}

	void LayerSystem::IterateForward(const std::function<void(Layer* const layer)>& handler) const
	{
		for (auto it = layerStack.crbegin(); it != layerStack.crend(); ++it) handler(*it);
	}

	void LayerSystem::IterateBackward(const std::function<void(Layer* const layer)>& handler) const
	{
		for (const auto it : layerStack) handler(it);
	}
}
