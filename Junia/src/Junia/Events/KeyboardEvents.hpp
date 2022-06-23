#pragma once

#include <functional>
#include <Junia/Events/Event.hpp>

namespace Junia
{
	class KeyboardKeyDownEvent : public Event
	{
	public:
		explicit KeyboardKeyDownEvent(const int button) : button(button) { }

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyDown; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("KeyboardKeyDownEvent(" << button << ")"); }

		[[nodiscard]] int GetButton() const { return button; }

	private:
		const int button;

		JE_EVENT_FUNCS_IMPL_Q(KeyboardKeyDownEvent)
	};

	class KeyboardKeyRepeatEvent : public Event
	{
	public:
		explicit KeyboardKeyRepeatEvent(const int button) : button(button) { }

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyRepeat; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("KeyboardKeyRepeatEvent(" << button << ")"); }

		[[nodiscard]] int GetButton() const { return button; }

	private:
		const int button;

		JE_EVENT_FUNCS_IMPL_Q(KeyboardKeyRepeatEvent)
	};

	class KeyboardKeyUpEvent : public Event
	{
	public:
		explicit KeyboardKeyUpEvent(const int button) : button(button) { }

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyUp; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("KeyboardKeyUpEvent(" << button << ")"); }

		[[nodiscard]] int GetButton() const { return button; }

	private:
		const int button;

		JE_EVENT_FUNCS_IMPL_Q(KeyboardKeyUpEvent)
	};

	class KeyboardKeyCharEvent : public Event
	{
	public:
		explicit KeyboardKeyCharEvent(const unsigned int codepoint) : codepoint(codepoint) { }

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyChar; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("KeyboardKeyCharEvent(" << codepoint << ")"); }

		[[nodiscard]] unsigned int GetCodepoint() const { return codepoint; }

	private:
		const unsigned int codepoint;

		JE_EVENT_FUNCS_IMPL_Q(KeyboardKeyCharEvent)
	};
}
