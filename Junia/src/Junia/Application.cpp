#include "Application.hpp"

#include <functional>
#include <Junia/Events/EventSystem.hpp>

namespace Junia
{
	Application* Application::app;

	Application::Application()
	{
		app = this;
		window = std::unique_ptr<Window>(Window::Create());
		WindowCloseEvent::Subscribe(JE_EVENTTYPE_BIND_MEMBER_FUNC(WindowCloseEvent, OnWindowClosed));
	}

	Application::~Application() = default;

	Layer* Application::PushLayerFront(Layer* layer) { return layerSystem.PushLayerFront(layer); }
	Layer* Application::PushLayerBack(Layer* layer) { return layerSystem.PushLayerBack(layer); }
	Layer* Application::PopLayerFront() { return layerSystem.PopLayerFront(); }
	Layer* Application::PopLayerBack() { return layerSystem.PopLayerBack(); }

	Window& Application::GetWindow() const { return *window; }
	Application& Application::Get() { return *app; }

	void Application::Run() const
	{
		while (running)
		{
			EventSystem::DispatchQueue();
			layerSystem.IterateForward([](Layer* layer) { layer->OnUpdate(); });
			window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(const WindowCloseEvent* e)
	{
		layerSystem.~LayerSystem();
		running = false;
		return true;
	}
}
