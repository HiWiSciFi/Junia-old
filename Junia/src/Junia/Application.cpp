#include "juniapch.hpp"
#include "Application.hpp"

#include "Junia/Log.hpp"

namespace Junia
{

	Application::Application() = default;

	Application::~Application() = default;

	void Application::Run()
	{
		JELOG_TRACE("{0}", "E");
		while(true);
	}

}