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
		[[nodiscard]] const char* ToString() const override { return "KeyboardKeyDownEvent"; }
	};

	class KeyboardKeyRepeatEvent : public Event
	{
	public:
		explicit KeyboardKeyRepeatEvent(const int button) : button(button) { }
		const int button;

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyRepeat; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] const char* ToString() const override { return "KeyboardKeyRepeatEvent"; }
	};

	class KeyboardKeyUpEvent : public Event
	{
	public:
		explicit KeyboardKeyUpEvent(const int button) : button(button) { }
		const int button;

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyUp; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] const char* ToString() const override { return "KeyboardKeyUpEvent"; }
	};

	class KeyboardKeyCharEvent : public Event
	{
	public:
		explicit KeyboardKeyCharEvent(const unsigned int codepoint) : codepoint(codepoint) { }
		const unsigned int codepoint;

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyChar; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] const char* ToString() const override { return "KeyboardKeyCharEvent"; }
	};
}
