#pragma once

#include "Events.hpp"

namespace Junia
{
	class JE_API_IO MouseMoveEvent : public Event
	{
	public:
		explicit MouseMoveEvent(const int x, const int y) : x(x), y(y) {  }
		const int x, y;

		[[nodiscard]] EventType GetType() const override { return EventType::MouseMove; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] const char* ToString() const override { return "MouseMoveEvent"; }
	};

	class JE_API_IO MouseButtonDownEvent : public Event
	{
	public:
		explicit MouseButtonDownEvent(const int button) : button(button) {  }
		const int button;

		[[nodiscard]] EventType GetType() const override { return EventType::MouseButtonDown; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] const char* ToString() const override { return "MouseButtonDownEvent"; }
	};

	class JE_API_IO MouseButtonUpEvent : public Event
	{
	public:
		explicit MouseButtonUpEvent(const int button) : button(button) { }
		const int button;

		[[nodiscard]] EventType GetType() const override { return EventType::MouseButtonUp; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] const char* ToString() const override { return "MouseButtonUpEvent"; }
	};
}
