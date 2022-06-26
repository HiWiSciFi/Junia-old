#include "Application.hpp"

#include <functional>

#include <Junia/Log.hpp>
#include <Junia/Events/EventSystem.hpp>
#include <Junia/Renderer/Renderer.hpp>
#include <Junia/UI/JUILayer.hpp>
#include <Junia/Platform/Platform.hpp>

namespace Junia
{
	Application* Application::app;

	Application::Application()
	{
		app = this;
		window = std::unique_ptr<Window>(Window::Create());
		WindowCloseEvent::Subscribe(JE_EVENTTYPE_BIND_MEMBER_FUNC(WindowCloseEvent, OnWindowClosed));
		PushLayerFront(new JUILayer());
	}

	Application::~Application() = default;

	Layer* Application::PushLayerFront(Layer* layer) { return layerSystem.PushLayerFront(layer); }
	Layer* Application::PushLayerBack(Layer* layer) { return layerSystem.PushLayerBack(layer); }
	Layer* Application::PopLayerFront() { return layerSystem.PopLayerFront(); }
	Layer* Application::PopLayerBack() { return layerSystem.PopLayerBack(); }

	void Application::Run()
	{
		while (running)
		{
			float time = Platform::GetTime();
			Timestep timestep = time - lastFrameTime;
			lastFrameTime = time;
			JELOG_BASE_TRACE("Timestep: %f", timestep.GetSeconds());

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
