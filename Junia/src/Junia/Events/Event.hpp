#pragma once

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

		KeyboardKeyDown,
		KeyboardKeyUp,

		WindowMove,
		WindowResize
	};

	class Event
	{
	public:
		virtual ~Event() = default;

		[[nodiscard]] virtual EventType GetType() const = 0;
		[[nodiscard]] virtual EventCategory GetCategory() const = 0;
		[[nodiscard]] virtual const char* ToString() const = 0;

	protected:
		Event() = default;
	};
}
