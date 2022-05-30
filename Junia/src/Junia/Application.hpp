#pragma once

#include <memory>

#include <Junia/Base.hpp>
#include <Junia/Window.hpp>
#include <Junia/Events/Event.hpp>

namespace Junia
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		bool OnEvent(const Event* e);

		Window& GetWindow();
		static Application& Get();

	private:
		bool OnWindowClosed(const Event* e);

		std::unique_ptr<Window> window;
		bool running = true;

		static Application* s_app;
	};

	// To be defined in client
	Application* CreateApplication();
}
