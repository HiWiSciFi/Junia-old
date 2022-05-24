#pragma once

#include "Event.hpp"

namespace Junia
{
	class KeyboardKeyDownEvent : public Event
	{
	public:
		explicit KeyboardKeyDownEvent(const int button) : button(button) { }
		const int button;

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyDown; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("KeyboardKeyDownEvent(" << button << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(KeyboardKeyDownEvent)
	};

	class KeyboardKeyRepeatEvent : public Event
	{
	public:
		explicit KeyboardKeyRepeatEvent(const int button) : button(button) { }
		const int button;

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyRepeat; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("KeyboardKeyRepeatEvent(" << button << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(KeyboardKeyRepeatEvent)
	};

	class KeyboardKeyUpEvent : public Event
	{
	public:
		explicit KeyboardKeyUpEvent(const int button) : button(button) { }
		const int button;

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyUp; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("KeyboardKeyUpEvent(" << button << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(KeyboardKeyUpEvent)
	};

	class KeyboardKeyCharEvent : public Event
	{
	public:
		explicit KeyboardKeyCharEvent(const unsigned int codepoint) : codepoint(codepoint) { }
		const unsigned int codepoint;

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyChar; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("KeyboardKeyCharEvent(" << codepoint << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(KeyboardKeyCharEvent)
	};
}
