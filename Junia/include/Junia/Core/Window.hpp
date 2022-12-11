#pragma once
#ifdef BUILD_JUNIA
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif
#include <inttypes.h>
#include <string>
#include <vector>

namespace Junia
{
	class Window
	{
	private:
		static std::vector<Window*> windows;

	public:
		using IdType = int32_t;

		/**
		* @brief Get the amount of currently opened windows
		* @return the amount of windows that have been opened but not closed yet
		*/
		static int GetWindowCount();
		/**
		* @brief Get a list of currently opened windows
		* @return a pointer to an array of Window* with a length of
		*         Window::GetWindowCount() + 1 elements where a Window::GetID()
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
		static Window* GetWindow(IdType id);
		/**
		* @brief Creates a window but does not open it
		* @param title the window title (UTF-8 supported)
		* @return a pointer to the created window
		*/
		static Window* Create(const std::string& title);
		/**
		* @brief Closes a window and frees all its assigned memory (All
		*        pointers to the specified window will be invalidated!)
		* @param id the ID of the window to destroy
		*/
		static void Destroy(IdType id);
		/**
		* @brief Closes a window and frees all its assigned memory (All
		*        pointers to the specified window will be invalidated!)
		* @param window a pointer of the window to destroy
		*/
		static void Destroy(const Window* window);

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

	private:
		IdType index = -1;
		bool open = false;
		std::string title;

		Window(const std::string& title);
		~Window();

	public:
		/**
		* @brief Gets the window ID
		* @return the window ID (value > 0) or -1 if the window isn't open
		*         (see Window::Open()). The window ID may change if another
		*         window is closed.
		*/
		IdType GetID();
		/**
		* @brief Gets the window title
		* @return the current window title (UTF-8 supported)
		*/
		const std::string& GetTitle();
		/**
		* @brief Sets the window title
		* @param title the new title for the window (UTF-8 supported)
		*/
		void SetTitle(const std::string& title);
		/**
		* @brief Checks if the window has been opened (see Window::Open())
		* @return true if the window is open, false otherwise
		*/
		bool IsOpen();

		/**
		* @brief Opens the window for the user to interact with. This function
		*        does nothing if the window already is open. The window ID
		*        (see Window::GetID()) will be set to a valid ID if successful
		*        and -1 otherwise.
		*/
		void Open();
		/**
		* @brief Closes the window and hides it from the user. This function
		*        does nothing if the window has already been closed or if it
		*        wasn't opened at all (see Window::Open()). The window ID
		*        (see Window::GetID()) will be set to -1.
		*/
		void Close();


		void Update();
	};
}
