#pragma once

#include "Events.hpp"
#include "../Core/Window.hpp"
#include "../Core/Keycodes.hpp"
#include "../../JMath/Vector2.hpp"

namespace Junia
{
	class KeyDownEvent : public Event
	{
	private:
		/**
		 * @brief The key that has been pressed
		*/
		KeyCode keyCode;

		/**
		 * @brief The window the key was pressed in
		*/
		Window* window;

	public:
		/**
		 * @brief Create a KeyDownEvent
		 * @param keyCode The KeyCode of the key that has been pressed
		 * @param window The window the key was pressed in
		*/
		KeyDownEvent(Window* window, KeyCode keyCode);

		/**
		 * @brief Get the key that has been pressed
		 * @return The KeyCode of the key
		*/
		KeyCode GetKeyCode() const;

		/**
		 * @brief Get the window the key was pressed on
		 * @return A pointer to the window
		*/
		Window* GetWindow() const;

		virtual std::string ToString() const override;
	};

	class KeyUpEvent : public Event
	{
	private:
		/**
		 * @brief The key that has been released
		*/
		KeyCode keyCode;

		/**
		 * @brief The window the key was released in
		*/
		Window* window;

	public:
		/**
		 * @brief Create a KeyUpEvent
		 * @param keyCode The KeyCode of the key that has been released
		 * @param window The window the key was released in
		*/
		KeyUpEvent(Window* window, KeyCode keyCode);

		/**
		 * @brief Get the key that has been released
		 * @return The KeyCode of the key
		*/
		KeyCode GetKeyCode() const;

		/**
		 * @brief Get the window the key was released on
		 * @return A pointer to the window
		*/
		Window* GetWindow() const;

		virtual std::string ToString() const override;
	};

	class KeyCharEvent : public Event
	{
	private:
		/**
		 * @brief The unicode codepoint that represents the character that has
		 *        been input
		*/
		unsigned int codepoint;

		/**
		 * @brief The window the character was sent to
		*/
		Window* window;

	public:
		/**
		 * @brief Create a KeyCharEvent
		 * @param codepoint The unicode codepoint of the character that has been
		 *                  input
		 * @param window The window the character was sent to
		*/
		KeyCharEvent(Window* window, unsigned int codepoint);

		/**
		 * @brief Get the character that has been input
		 * @return The unicode codepoint of the character
		*/
		unsigned int GetCodepoint() const;

		/**
		 * @brief Get the window the character was sent to
		 * @return A pointer to the window
		*/
		Window* GetWindow() const;

		virtual std::string ToString() const override;
	};

	class MouseButtonDownEvent : public Event
	{
	private:
		/**
		 * @brief The button that has been pressed
		*/
		MouseButton button;

		/**
		 * @brief The window the button was pressed in
		*/
		Window* window;

	public:
		/**
		 * @brief Create a MouseButtonDownEvent
		 * @param button The button that has been pressed
		 * @param window The window the button was pressed in
		*/
		MouseButtonDownEvent(Window* window, MouseButton button);

		/**
		 * @brief Get the mouse button that has been pressed
		 * @return The MouseButton that has been pressed
		*/
		MouseButton GetButton() const;

		/**
		 * @brief Get the window the button was pressed in
		 * @return A pointer to the window
		*/
		Window* GetWindow() const;

		virtual std::string ToString() const override;
	};

	class MouseButtonUpEvent : public Event
	{
	private:
		/**
		 * @brief The button that has been released
		*/
		MouseButton button;

		/**
		 * @brief The window the button was released in
		*/
		Window* window;

	public:
		/**
		 * @brief Create a MouseButtonUpEvent
		 * @param button The mouse button that has been released
		 * @param window The window the button was released in
		*/
		MouseButtonUpEvent(Window* window, MouseButton button);

		/**
		 * @brief Get the mouse button that has been released
		 * @return The MouseButton that has been released
		*/
		MouseButton GetButton() const;

		/**
		 * @brief Get the window the button was released in
		 * @return A pointer to the window
		*/
		Window* GetWindow() const;

		virtual std::string ToString() const override;
	};

	class MouseMoveEvent : public Event
	{
	private:
		/**
		 * @brief The new position of the mouse
		*/
		JMath::iVec2 position;

		/**
		 * @brief The window the mouse was moved in
		*/
		Window* window;

	public:
		/**
		 * @brief Create a MouseMoveEvent
		 * @param position The new position of the mouse cursor
		 * @param window The window the mouse was moved in
		*/
		MouseMoveEvent(Window* window, JMath::iVec2 position);

		/**
		 * @brief Get the new position of the mouse
		 * @return The position of the mouse cursor
		*/
		JMath::iVec2 GetPosition() const;

		/**
		 * @brief Get the window the mouse was moved in
		 * @return A pointer to the window
		*/
		Window* GetWindow() const;

		virtual std::string ToString() const override;
	};
}
