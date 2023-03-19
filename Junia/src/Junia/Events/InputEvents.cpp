#include <Junia/Events/InputEvents.hpp>
#include <sstream>

namespace Junia
{

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- KeyDownEvent ---------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

	KeyDownEvent::KeyDownEvent(KeyCode keyCode) : keyCode(keyCode) { }
	KeyCode KeyDownEvent::GetKeyCode() const { return keyCode; }
	std::string KeyDownEvent::ToString() const
	{
		std::stringstream ss;
		ss << "KeyDownEvent(" << KeyToString(keyCode) << ")";
		return ss.str();
	}

// ---------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------- KeyUpEvent ----------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

	KeyUpEvent::KeyUpEvent(KeyCode keyCode) : keyCode(keyCode) { }
	KeyCode KeyUpEvent::GetKeyCode() const { return keyCode; }
	std::string KeyUpEvent::ToString() const
	{
		std::stringstream ss;
		ss << "KeyUpEvent(" << KeyToString(keyCode) << ")";
		return ss.str();
	}

// ---------------------------------------------------------------------------------------------------------------------
// ---------------------------------------------------- KeyCharEvent ---------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

	KeyCharEvent::KeyCharEvent(unsigned int codepoint) : codepoint(codepoint) { }
	unsigned int KeyCharEvent::GetCodepoint() const { return codepoint; }
	std::string KeyCharEvent::ToString() const
	{
		std::stringstream ss;
		ss << "KeyCharEvent(" << static_cast<wchar_t>(codepoint) << ")";
		return ss.str();
	}

// ---------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------ MouseButtonDownEvent -----------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

	MouseButtonDownEvent::MouseButtonDownEvent(MouseButton button) : button(button) { }
	MouseButton MouseButtonDownEvent::GetButton() const { return button; }
	std::string MouseButtonDownEvent::ToString() const
	{
		std::stringstream ss;
		ss << "MouseButtonDownEvent(" << MouseButtonToString(button) << ")";
		return ss.str();
	}

// ---------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------- MouseButtonUpEvent ------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

	MouseButtonUpEvent::MouseButtonUpEvent(MouseButton button) : button(button) { }
	MouseButton MouseButtonUpEvent::GetButton() const { return button; }
	std::string MouseButtonUpEvent::ToString() const
	{
		std::stringstream ss;
		ss << "MouseButtonUpEvent(" << MouseButtonToString(button) << ")";
		return ss.str();
	}

// ---------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------- MouseMoveEvent --------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

	MouseMoveEvent::MouseMoveEvent(JMath::iVec2 position) : position(position) { }
	JMath::iVec2 MouseMoveEvent::GetPosition() const { return position; }
	std::string MouseMoveEvent::ToString() const
	{
		std::stringstream ss;
		ss << "MouseMoveEvent(" << position.x << ", " << position.y << ")";
		return ss.str();
	}
}
