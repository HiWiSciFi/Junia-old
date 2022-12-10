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
		/**
		* @brief Get the amount of currently opened windows
		* @return the amount of windows that have been opened but not closed yet
		*/
		static int GetWindowCount();
		/**
		* @brief Get a list of currently opened windows
		* @return a pointer to an array of Window* with a length of
		*         Window::GetWindowCount() + 1 Elements where a Window::GetID()
		*         is the index of the window and the the element at index 0 is
		*         the currently focused window or nullptr
		*/
		static Window** const GetWindows();
		/**
		* @brief Get a window by its ID
		* @param id the ID of the window to fetch
		* @return a pointer to the window with the specified ID or a nullptr if
		*         there is no currently opened window with that ID
		*/
		static Window* GetWindow(int id);

		/**
		* @brief Creates a window but does not open it
		* @return a pointer to the created window
		*/
		static Window* CreateWindow();
		/**
		* @brief Closes a window and frees all its assigned memory (All
		*        pointers to the specified window will be invalidated!)
		* @param id the ID of the window to destroy
		*/
		static void DestroyWindow(int id);
		/**
		* @brief Closes a window and frees all its assigned memory (All
		*        pointers to the specified window will be invalidated!)
		* @param window a pointer of the window to destroy
		*/
		static void DestroyWindow(const Window* window);

	private:
		int index;

	public:
#ifdef BUILD_JUNIA
		/**
		* @brief The pointer to the underlying glfw window structure (DO NOT
		*        EDIT THIS VALUE)
		*/
		GLFWwindow* nativeWindow;
#else
		/**
		* @brief The pointer to the underlying glfw window structure (DO NOT
		*        EDIT THIS VALUE)
		*/
		void* nativeWindow;
#endif

		bool shouldClose = false;

	protected:
		Window();
		~Window();

	public:
		void Open();
		void Close();

		int GetID();
		void Update();
	};
}
