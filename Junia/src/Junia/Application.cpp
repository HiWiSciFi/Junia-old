#include "juniapch.hpp"
#include "Application.hpp"

#include "Events/ApplicationEvent.hpp"
#include "Junia/Log.hpp"

namespace Junia
{

	Application::Application() = default;

	Application::~Application() = default;

	void Application::Run()
	{
		WindowResizeEvent const e(1280, 720);
		JELOG_TRACE("{0}", e);
		while(true);
	}

}