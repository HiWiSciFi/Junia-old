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
		WindowResizeEvent::Subscribe(JE_EVENTTYPE_BIND_MEMBER_FUNC(WindowResizeEvent, OnWindowResize));

		Renderer::Init();

		PushLayerFront(new JUILayer());
	}

	Application::~Application() = default;

	Layer* Application::PushLayerFront(Layer* layer) { return layerSystem.PushLayerFront(layer); }
	Layer* Application::PushLayerBack(Layer* layer) { return layerSystem.PushLayerBack(layer); }
	Layer* Application::PopLayerFront() { return layerSystem.PopLayerFront(); }
	Layer* Application::PopLayerBack() { return layerSystem.PopLayerBack(); }

	void Application::Run()
	{
		lastFrameTime = Platform::GetTime();
		while (running)
		{
			float time = Platform::GetTime();
			Timestep timestep = time - lastFrameTime;
			lastFrameTime = time;

			EventSystem::DispatchQueue();
			if (!minimized) layerSystem.IterateForward([timestep](Layer* layer) { layer->OnUpdate(timestep); layer->OnUpdate(); });
			window->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(const WindowCloseEvent& e)
	{
		layerSystem.~LayerSystem();
		running = false;
		return true;
	}

	bool Application::OnWindowResize(const WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			minimized = true;
		}
		minimized = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}
