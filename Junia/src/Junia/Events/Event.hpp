#pragma once

#include <sstream>

namespace Junia
{
	enum class EventCategory
	{
		Input,
		Window
	};

	enum class EventType
	{
		MouseMove,
		MouseButtonDown,
		MouseButtonUp,
		MouseScroll,

		KeyboardKeyDown,
		KeyboardKeyRepeat,
		KeyboardKeyUp,
		KeyboardKeyChar,

		JoystickConnect,

		WindowClose,
		WindowMove,
		WindowResize,
		WindowMaximize,
		WindowFocus
	};

#define JE_EVENT_TOSTR_MCR(x) std::stringstream ss; ss << ##x; return ss.str()

	class Event
	{
	public:
		virtual ~Event() = default;

		[[nodiscard]] virtual EventType GetType() const = 0;
		[[nodiscard]] virtual EventCategory GetCategory() const = 0;
		[[nodiscard]] virtual std::string ToString() const = 0;

	protected:
		Event() = default;
	};
}
