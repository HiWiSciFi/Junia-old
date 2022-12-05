#pragma once
#ifdef BUILD_JUNIA
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif

namespace Junia
{
	class Window
	{
	private:
		#ifdef BUILD_JUNIA
		GLFWwindow* window;
		#else
		void* window;
		#endif

	public:
		bool shouldClose = false;

		Window();
		~Window();

		void Update();
	};
}
