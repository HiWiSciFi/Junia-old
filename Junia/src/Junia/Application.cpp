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
		JELOG_BASE_TRACE("Initializing GLFW...");
		if (!glfwInit()) { JELOG_BASE_CRIT("GLFW could not be initialized!"); return; }
		JELOG_BASE_TRACE("GLFW Initialized!");

		GLFWwindow* window = glfwCreateWindow(640, 480, "Application", NULL, NULL);
		if (!window) { glfwTerminate(); return; }
		glfwMakeContextCurrent(window);
		while (!glfwWindowShouldClose(window)) {
			//glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		JELOG_BASE_TRACE("Shutting down GLFW...");
		glfwTerminate();
		JELOG_BASE_TRACE("GLFW stopped!");

		while (true);
	}
}