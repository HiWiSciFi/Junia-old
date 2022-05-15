#include "Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <Junia/Log.hpp>

namespace Junia
{
	Application::Application() = default;

	Application::~Application() = default;

	void Application::Run()
	{
		JELOG_BASE_TRACE("Initializing GLFW...");
		if (!glfwInit()) { JELOG_BASE_CRIT("GLFW could not be initialized!"); return; }
		JELOG_BASE_TRACE("GLFW Initialized!");

		// GLFW Window test code

		GLFWwindow* window = glfwCreateWindow(640, 480, "Application", NULL, NULL);
		if (!window) { glfwTerminate(); return; }
		glfwMakeContextCurrent(window);
		gladLoadGL();
		while (!glfwWindowShouldClose(window)) {
			glClearColor(0, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		// END GLFW Window test code

		JELOG_BASE_TRACE("Shutting down GLFW...");
		glfwTerminate();
		JELOG_BASE_TRACE("GLFW stopped!");

		while (true);
	}
}
