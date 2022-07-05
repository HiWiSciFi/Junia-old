#pragma once

#include <memory>

#include <Junia/Core/Window.hpp>
#include <Junia/Core/LayerSystem.hpp>
#include <Junia/Events/WindowEvents.hpp>
#include <Junia/Core/Timestep.hpp>

namespace Junia
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		Layer* PushLayerFront(Layer* layer);
		Layer* PushLayerBack(Layer* layer);
		Layer* PopLayerFront();
		Layer* PopLayerBack();

		[[nodiscard]] Window& GetWindow() const { return *window; }
		static Application& Get() { return *app; }

	private:
		bool OnWindowClosed(const WindowCloseEvent& e);
		bool OnWindowResize(const WindowResizeEvent& e);

		std::unique_ptr<Window> window;
		LayerSystem layerSystem;
		bool running = true;
		float lastFrameTime = 0.0f;
		bool minimized = false;

		static Application* app;
	};

	// To be defined in client
	Application* CreateApplication();
}
