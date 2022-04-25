#include "juniapch.hpp"
#include "Application.hpp"

#include "Junia/Log.hpp"

#include <GLFW/glfw3.h>

namespace Junia
{

	Application::Application() = default;

	Application::~Application() = default;

	void Application::Run()
	{
		//if (!glfwInit()) JELOG_CRIT("{0}", "GLFW could not be initialized!");
		JELOG_TRACE("{0}", "E");
		//glfwTerminate();
		while (true);
	}

}