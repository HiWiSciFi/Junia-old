#pragma once

#include <Junia/Events/Events.hpp>
#include <Junia/Core/Keycodes.hpp>
#include <JMath/Vector2.hpp>
#include <string>

namespace Junia
{
	class KeyDownEvent : public Event
	{
	private:
		/**
		 * @brief The key that has been pressed
		*/
		KeyCode keyCode;

	public:
		/**
		 * @brief Create a KeyDownEvent
		 * @param keyCode The KeyCode of the key that has been pressed
		*/
		KeyDownEvent(KeyCode keyCode);

		/**
		 * @brief Get the key that has been pressed
		 * @return The KeyCode of the key
		*/
		KeyCode GetKeyCode() const;

		virtual std::string ToString() const override;
	};

	class KeyUpEvent : public Event
	{
	private:
		/**
		 * @brief The key that has been released
		*/
		KeyCode keyCode;

	public:
		/**
		 * @brief Create a KeyUpEvent
		 * @param keyCode The KeyCode of the key that has been released
		*/
		KeyUpEvent(KeyCode keyCode);

		/**
		 * @brief Get the key that has been released
		 * @return The KeyCode of the key
		*/
		KeyCode GetKeyCode() const;

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

	public:
		/**
		 * @brief Create a KeyCharEvent
		 * @param codepoint The unicode codepoint of the character that has been
		 *                  input
		*/
		KeyCharEvent(unsigned int codepoint);

		/**
		 * @brief Get the character that has been input
		 * @return The unicode codepoint of the character
		*/
		unsigned int GetCodepoint() const;

		virtual std::string ToString() const override;
	};

	class MouseButtonDownEvent : public Event
	{
	private:
		/**
		 * @brief The button that has been pressed
		*/
		MouseButton button;

	public:
		/**
		 * @brief Create a MouseButtonDownEvent
		 * @param button The button that has been pressed
		*/
		MouseButtonDownEvent(MouseButton button);

		/**
		 * @brief Get the mouse button that has been pressed
		 * @return The MouseButton that has been pressed
		*/
		MouseButton GetButton() const;

		virtual std::string ToString() const override;
	};

	class MouseButtonUpEvent : public Event
	{
	private:
		/**
		 * @brief The button that has been released
		*/
		MouseButton button;

	public:
		/**
		 * @brief Create a MouseButtonUpEvent
		 * @param button The mouse button that has been released
		*/
		MouseButtonUpEvent(MouseButton button);

		/**
		 * @brief Get the mouse button that has been released
		 * @return The MouseButton that has been released
		*/
		MouseButton GetButton() const;

		virtual std::string ToString() const override;
	};

	class MouseMoveEvent : public Event
	{
	private:
		/**
		 * @brief The new position of the mouse
		*/
		JMath::iVec2 position;

	public:
		/**
		 * @brief Create a MouseMoveEvent
		 * @param position The new position of the mouse cursor
		*/
		MouseMoveEvent(JMath::iVec2 position);

		/**
		 * @brief Get the new position of the mouse
		 * @return The position of the mouse cursor
		*/
		JMath::iVec2 GetPosition() const;

		virtual std::string ToString() const override;
	};
}
