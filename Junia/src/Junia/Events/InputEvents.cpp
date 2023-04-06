#include <Junia/Events/InputEvents.hpp>
#include <sstream>

namespace Junia
{

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- KeyDownEvent ---------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

	KeyDownEvent::KeyDownEvent(Window* window, KeyCode keyCode) : window(window), keyCode(keyCode) { }
	KeyCode KeyDownEvent::GetKeyCode() const { return keyCode; }
	Window* KeyDownEvent::GetWindow() const { return window; }
	std::string KeyDownEvent::ToString() const
	{
		std::stringstream ss;
		ss << "KeyDownEvent(" << KeyToString(keyCode) << ")";
		return ss.str();
	}

// ---------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- KeyUpEvent ----------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

	KeyUpEvent::KeyUpEvent(Window* window, KeyCode keyCode) : window(window), keyCode(keyCode) { }
	KeyCode KeyUpEvent::GetKeyCode() const { return keyCode; }
	Window* KeyUpEvent::GetWindow() const { return window; }
	std::string KeyUpEvent::ToString() const
	{
		std::stringstream ss;
		ss << "KeyUpEvent(" << KeyToString(keyCode) << ")";
		return ss.str();
	}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- KeyCharEvent ---------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

	KeyCharEvent::KeyCharEvent(Window* window, unsigned int codepoint) : window(window), codepoint(codepoint) { }
	unsigned int KeyCharEvent::GetCodepoint() const { return codepoint; }
	Window* KeyCharEvent::GetWindow() const { return window; }
	std::string KeyCharEvent::ToString() const
	{
		std::stringstream ss;
		ss << "KeyCharEvent(" << static_cast<char>(codepoint) << ")";
		return ss.str();
	}

// ---------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------ MouseButtonDownEvent -----------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

	MouseButtonDownEvent::MouseButtonDownEvent(Window* window, MouseButton button) : window(window), button(button) { }
	MouseButton MouseButtonDownEvent::GetButton() const { return button; }
	Window* MouseButtonDownEvent::GetWindow() const { return window; }
	std::string MouseButtonDownEvent::ToString() const
	{
		std::stringstream ss;
		ss << "MouseButtonDownEvent(" << MouseButtonToString(button) << ")";
		return ss.str();
	}

// ---------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------- MouseButtonUpEvent ------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

	MouseButtonUpEvent::MouseButtonUpEvent(Window* window, MouseButton button) : window(window), button(button) { }
	MouseButton MouseButtonUpEvent::GetButton() const { return button; }
	Window* MouseButtonUpEvent::GetWindow() const { return window; }
	std::string MouseButtonUpEvent::ToString() const
	{
		std::stringstream ss;
		ss << "MouseButtonUpEvent(" << MouseButtonToString(button) << ")";
		return ss.str();
	}

// ---------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- MouseMoveEvent --------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

	MouseMoveEvent::MouseMoveEvent(Window* window, JMath::Vec2i position) : window(window), position(position) { }
	JMath::Vec2i MouseMoveEvent::GetPosition() const { return position; }
	Window* MouseMoveEvent::GetWindow() const { return window; }
	std::string MouseMoveEvent::ToString() const
	{
		std::stringstream ss;
		ss << "MouseMoveEvent(" << position.x << ", " << position.y << ")";
		return ss.str();
	}
}
