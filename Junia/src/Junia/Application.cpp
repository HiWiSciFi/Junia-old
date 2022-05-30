#include "Application.hpp"

#include <functional>

#include <Junia/Log.hpp>
#include <Junia/Events/EventSystem.hpp>

namespace Junia
{
	Application* Application::s_app;

	Application::Application()
	{
		s_app = this;
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

	Window& Application::GetWindow()
	{
		return *window.get();
	}

	Application& Application::Get()
	{
		return *s_app;
	}

	void Application::Run()
	{
		//const auto w = std::unique_ptr<Window>(Window::Create(WindowProperties("Subwindow", 200, 300)));
		while (running)
		{
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
