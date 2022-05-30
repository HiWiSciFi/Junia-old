#pragma once

#include <Junia/Events/Event.hpp>

namespace Junia
{
	class MouseMoveEvent : public Event
	{
	public:
		explicit MouseMoveEvent(const float x, const float y) : x(x), y(y) {  }
		const float x;
		const float y;

		EventType GetType() const override { return EventType::MouseMove; }
		EventCategory GetCategory() const override { return EventCategory::Input; }
		std::string ToString() const override { JE_EVENT_TOSTR_MCR("MouseMoveEvent(" << x << "," << y << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(MouseMoveEvent)
	};

	class MouseButtonDownEvent : public Event
	{
	public:
		explicit MouseButtonDownEvent(const int button) : button(button) {  }
		const int button;

		EventType GetType() const override { return EventType::MouseButtonDown; }
		EventCategory GetCategory() const override { return EventCategory::Input; }
		std::string ToString() const override { JE_EVENT_TOSTR_MCR("MouseButtonDownEvent(" << button << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(MouseButtonDownEvent)
	};

	class MouseButtonUpEvent : public Event
	{
	public:
		explicit MouseButtonUpEvent(const int button) : button(button) { }
		const int button;

		EventType GetType() const override { return EventType::MouseButtonUp; }
		EventCategory GetCategory() const override { return EventCategory::Input; }
		std::string ToString() const override { JE_EVENT_TOSTR_MCR("MouseButtonUpEvent(" << button << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(MouseButtonUpEvent)
	};

	class MouseScrollEvent : public Event
	{
	public:
		explicit MouseScrollEvent(const float xOffset, const float yOffset) : xOffset(xOffset), yOffset(yOffset) { }
		const float xOffset;
		const float yOffset;

		EventType GetType() const override { return EventType::MouseScroll; }
		EventCategory GetCategory() const override { return EventCategory::Input; }
		std::string ToString() const override { JE_EVENT_TOSTR_MCR("MouseScrollEvent(" << xOffset << "," << yOffset << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(MouseScrollEvent)
	};
}
