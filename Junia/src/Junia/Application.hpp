#pragma once

#include <memory>

#include <Junia/Window.hpp>

#include <Junia/LayerSystem.hpp>
#include <Junia/Events/WindowEvents.hpp>

namespace Junia
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run() const;

		Layer* PushLayerFront(Layer* layer);
		Layer* PushLayerBack(Layer* layer);
		Layer* PopLayerFront();
		Layer* PopLayerBack();

		[[nodiscard]] Window& GetWindow() const;
		static Application& Get();

	private:
		bool OnWindowClosed(const WindowCloseEvent* e);

		std::unique_ptr<Window> window;
		LayerSystem layerSystem;
		bool running = true;

		static Application* app;
	};

	// To be defined in client
	Application* CreateApplication();
}
