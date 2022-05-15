#pragma once

#include <memory>

#include "Base.hpp"
#include "Window.hpp"
#include "Events/Event.hpp"

namespace Junia
{
	class JE_API_IO Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		bool OnEvent(const Event* e);

	private:
		bool OnWindowClosed(const Event* e);

		std::unique_ptr<Window> window;
		bool running = true;
	};

	// To be defined in client
	Application* CreateApplication();
}
