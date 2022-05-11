#pragma once

#include "Events.hpp"

namespace Junia
{
	class JE_API_IO KeyboardKeyDownEvent : public Event
	{
	public:
		explicit KeyboardKeyDownEvent(const int button) : button(button) { }
		const int button;

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyDown; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] const char* ToString() const override { return "KeyboardKeyDownEvent"; }
	};

	class JE_API_IO KeyboardKeyUpEvent : public Event
	{
	public:
		explicit KeyboardKeyUpEvent(const int button) : button(button) { }
		const int button;

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyUp; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] const char* ToString() const override { return "KeyboardKeyUpEvent"; }
	};
}
