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
		static std::vector<Window*> windows;

	public:
		static int GetWindowCount();
		static Window** GetWindows();
		static Window* GetWindow(int id);

		static Window* CreateWindow();
		static void DestroyWindow(int id);
		static void DestroyWindow(Window* window);

	private:
		int index;

	public:

#ifdef BUILD_JUNIA
		GLFWwindow* nativeWindow;
#else
		void* nativeWindow;
#endif

		bool shouldClose = false;

		Window();
		~Window();

		int GetID();
		void Update();
	};
}
