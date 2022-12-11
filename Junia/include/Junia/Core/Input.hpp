#pragma once
#include <utility>
#include <inttypes.h>
#include <Junia/Core/Window.hpp>
#include <Junia/Core/Keycodes.hpp>

namespace Junia
{
	class Input
	{
	public:
		/**
		 * @brief Get if a key is pressed
		 * @param keycode the KeyCode of the key to check for
		 * @param window the ID of the window to check the key state for
		 * @return true if the key is pressed, false otherwise
		*/
		static bool IsKeyDown(KeyCode keycode, Window::IdType window = 0);
		/**
		 * @brief Get if a mouse button is pressed
		 * @param button the mouse button to check for
		 * @param window the ID of the window to check the mouse state for
		 * @return true if the button is pressed, false otherwise
		*/
		static bool IsMouseButtonDown(MouseButton button, Window::IdType window = 0);
		/**
		 * @brief Get the position of the mouse in a window
		 * @param window the ID of the window relative to which to get the mouse
		 *               position
		 * @return a pair of { x, y } containing the x and y position of the
		 *           mouse
		*/
		static std::pair<int, int> GetMousePosition(Window::IdType window = 0);

		/**
		 * @brief Get if a key is not pressed
		 * @param keycode the KeyCode of the key to check for
		 * @param window the ID of the window to check the key state for
		 * @return true if the key is not pressed, false otherwise
		*/
		static inline bool IsKeyUp(KeyCode keycode, Window::IdType window = 0)
			{ return !IsKeyDown(keycode, window); }
		/**
		 * @brief Get if a mouse button is not pressed
		 * @param button the mouse button to check for
		 * @param window the ID of the window to check the mouse state for
		 * @return true if the button is not pressed, false otherwise
		*/
		static inline bool IsMouseButtonUp(MouseButton button, Window::IdType window = 0)
			{ return !IsMouseButtonDown(button, window); }
		/**
		 * @brief Get the x position of the mouse
		 * @param window the ID of the window relative to which to get the mouse
		 *               position
		 * @return the x position of the mouse
		*/
		static inline int GetMouseX(Window::IdType window = 0)
			{ return GetMousePosition(window).first; }
		/**
		 * @brief Get the y position of the mouse
		 * @param window the ID of the window relative to which to get the mouse
		 *               position
		 * @return the y position of the mouse
		*/
		static inline int GetMouseY(Window::IdType window = 0)
			{ return GetMousePosition(window).second; }
	};
}
