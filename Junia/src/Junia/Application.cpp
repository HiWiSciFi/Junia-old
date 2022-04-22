#include "juniapch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Junia/Log.h"

namespace Junia
{

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent const e(1280, 720);
		JE_TRACE(e);
		while(true);
	}

}