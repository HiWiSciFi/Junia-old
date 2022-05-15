#pragma once

#include "Event.hpp"

namespace Junia
{
	class MouseMoveEvent : public Event
	{
	public:
		explicit MouseMoveEvent(const float x, const float y) : x(x), y(y) {  }
		const float x;
		const float y;

		[[nodiscard]] EventType GetType() const override { return EventType::MouseMove; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] const char* ToString() const override { return "MouseMoveEvent"; }
	};

	class MouseButtonDownEvent : public Event
	{
	public:
		explicit MouseButtonDownEvent(const int button) : button(button) {  }
		const int button;

		[[nodiscard]] EventType GetType() const override { return EventType::MouseButtonDown; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] const char* ToString() const override { return "MouseButtonDownEvent"; }
	};

	class MouseButtonUpEvent : public Event
	{
	public:
		explicit MouseButtonUpEvent(const int button) : button(button) { }
		const int button;

		[[nodiscard]] EventType GetType() const override { return EventType::MouseButtonUp; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] const char* ToString() const override { return "MouseButtonUpEvent"; }
	};

	class MouseScrollEvent : public Event
	{
	public:
		explicit MouseScrollEvent(const float xOffset, const float yOffset) : xOffset(xOffset), yOffset(yOffset) { }
		const float xOffset;
		const float yOffset;

		[[nodiscard]] EventType GetType() const override { return EventType::MouseScroll; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] const char* ToString() const override { return "MouseScrollEvent"; }
	};
}
