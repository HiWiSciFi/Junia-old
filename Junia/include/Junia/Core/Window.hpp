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
		* @return a pointer to the window with the specified ID or nullptr if
		*         there is no currently opened window with that ID. Call with
		*         ID 0 to get a pointer to the currently focused window
		*/
		static Window* GetWindow(IdType id);
		/**
		 * @brief Get the currently focused window
		 * @return a pointer to the currently focused window or nullptr if no
		 *         window is currently focused
		*/
		static Window* GetWindow();
		/**
		* @brief Create a window. The window isn't opened automatically. (see
		*        Window::Open())
		* @param title the window title (UTF-8 supported)
		* @return a pointer to the created window
		*/
		static Window* Create(const std::string& title);
		/**
		* @brief Close a window and free all its assigned memory (All
		*        pointers to the specified window will be invalidated!)
		* @param id the ID of the window to destroy
		*/
		static void Destroy(IdType id);
		/**
		* @brief Close a window and free all its assigned memory (All
		*        pointers to the specified window will be invalidated!)
		* @param window a pointer of the window to destroy
		*/
		static void Destroy(const Window* window);

#ifdef BUILD_JUNIA
	public:
		/**
		* @brief The pointer to the underlying glfw window structure (DO NOT
		*        EDIT THIS VALUE)
		*/
		GLFWwindow* nativeWindow;
#else
	private:
		/**
		* @brief The pointer to the underlying glfw window structure (DO NOT
		*        EDIT THIS VALUE)
		*/
		void* nativeWindow;
#endif
		IdType index = -1;
		bool open = false;
		bool focused = false;
		std::string title;

		Window(const std::string& title);
		~Window();

	public:
		/**
		* @brief Get the window ID
		* @return the window ID (value &gt; 0) or -1 if the window isn't open
		*         (see Window::Open()). The window ID may change if another
		*         window is closed.
		*/
		IdType GetID();
		/**
		* @brief Get the window title
		* @return the current window title (UTF-8 supported)
		*/
		const std::string& GetTitle();
		/**
		* @brief Set the window title
		* @param title the new title for the window (UTF-8 supported)
		*/
		void SetTitle(const std::string& title);

		// TODO: Window position and size for non opened windows + errors

		/**
		 * @brief Get the window position
		 * @return a pair containing the window postion as { x, y }
		*/
		std::pair<int, int> GetPosition();
		/**
		 * @brief Set the window position
		 * @param position the position to move the window to as { x, y }
		*/
		void SetPosition(std::pair<int, int> position);
		/**
		 * @brief Get the window size
		 * @return a pair containing the window size as { width, height }
		*/
		std::pair<int, int> GetSize();
		/**
		 * @brief Set the window size
		 * @param size the new size for the window as { width, height }
		*/
		void SetSize(std::pair<int, int> size);

		// TODO: implement size limit setting / getting
		// TODO: implement aspect ratio getting / setting

		/**
		 * @brief Get the window opacity
		 * @return the window opacity (0.0: translucent - 1.0: opaque)
		*/
		float GetOpacity();
		/**
		 * @brief Set the window opacity
		 * @param opacity the new opacity for the window as a value between 0.0
		 *                and 1.0 (0.0: translucent - 1.0: opaque)
		*/
		void SetOpacity(float opacity);

		// TODO: implement iconify, restore, maximize
		// TODO: implement show, hide

		/**
		* @brief Get if the window has been opened (see Window::Open())
		* @return true if the window is open, false otherwise
		*/
		bool IsOpen();

		/**
		* @brief Open the window for the user to interact with. This function
		*        does nothing if the window already is open. The window ID
		*        (see Window::GetID()) will be set to a valid ID if successful
		*        and -1 otherwise.
		*/
		void Open();
		/**
		* @brief Close the window and hides it from the user. This function
		*        does nothing if the window has already been closed or if it
		*        wasn't opened at all (see Window::Open()). The window ID
		*        (see Window::GetID()) will be set to -1.
		*/
		void Close();

		/**
		 * @brief Get if the window is in focus. Focus can be requested using
		 *        Window::Focus().
		 * @return true if the window is in focus, false otherwise
		*/
		bool IsFocused();

		/**
		 * @brief Request to focus this window. If the window is not open (see
		 *        Window::IsOpen()) this function will have no effect.
		*/
		void Focus();


		void Update();
	};
}
