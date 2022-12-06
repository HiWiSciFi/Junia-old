#pragma once
#ifdef BUILD_JUNIA
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif
#include <vector>

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
		int index;

		static std::vector<Window*> windows;

	public:
		static int GetWindowCount();
		static Window** GetWindows();
		static Window* GetWindow(int id);


		bool shouldClose = false;

		Window();
		~Window();

		int GetID();
		void Update();
	};
}
