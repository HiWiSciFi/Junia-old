#pragma once

#include <functional>
#include <Junia/Events/Event.hpp>

namespace Junia
{
	class KeyboardKeyDownEvent : public Event
	{
	public:
		explicit KeyboardKeyDownEvent(const int keyCode) : keyCode(keyCode) { }

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyDown; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("KeyboardKeyDownEvent(" << keyCode << ")"); }

		[[nodiscard]] int GetKeyCode() const { return keyCode; }

	private:
		const int keyCode;

		JE_EVENT_FUNCS_IMPL_Q(KeyboardKeyDownEvent)
	};

	class KeyboardKeyUpEvent : public Event
	{
	public:
		explicit KeyboardKeyUpEvent(const int keyCode) : keyCode(keyCode) { }

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyUp; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("KeyboardKeyUpEvent(" << keyCode << ")"); }

		[[nodiscard]] int GetButton() const { return keyCode; }

	private:
		const int keyCode;

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
