#include "Application.hpp"

#include <functional>

#include "Events/EventSystem.hpp"
#include <glad/glad.h>

#include "Log.hpp"
#include "Events/WindowEvents.hpp"
#include <Junia/Events/MouseEvents.hpp>

namespace Junia
{
	Application::Application()
	{
		window = std::unique_ptr<Window>(Window::Create());
		EventSystem::Subscribe(std::bind(&Application::OnEvent, this, std::placeholders::_1));
		EventSystem::Subscribe(std::bind(&Application::OnWindowClosed, this, std::placeholders::_1));
	}

	Application::~Application() = default;

	bool Application::OnEvent(const Event* e)
	{
		JELOG_BASE_TRACE("Event Triggered: {0}", e->ToString());
		return false;
	}

	void Application::Run()
	{
		//const auto w = std::unique_ptr<Window>(Window::Create(WindowProperties("Subwindow", 200, 300)));
		while (running)
		{
			glClearColor(0, .3f, .3f, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			EventSystem::DispatchQueue();
			window->OnUpdate();
			//w->OnUpdate();
		}
	}

	bool Application::OnWindowClosed(const Event* e)
	{
		if (e->GetType() != EventType::WindowClose) return false;
		running = false;
		return true;
	}
}
