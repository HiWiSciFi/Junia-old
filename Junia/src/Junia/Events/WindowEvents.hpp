#pragma once

#include <Junia/Events/Event.hpp>

namespace Junia
{
	class WindowCloseEvent : public Event
	{
	public:
		explicit WindowCloseEvent() = default;

		EventType GetType() const override { return EventType::WindowClose; }
		EventCategory GetCategory() const override { return EventCategory::Window; }
		std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowCloseEvent()"); }

		JE_EVENT_FUNCS_IMPL_Q(WindowCloseEvent)
	};

	class WindowMoveEvent : public Event
	{
	public:
		explicit WindowMoveEvent(const int x, const int y) : x(x), y(y) { }
		const int x;
		const int y;

		EventType GetType() const override { return EventType::WindowMove; }
		EventCategory GetCategory() const override { return EventCategory::Window; }
		std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowMoveEvent(" << x << "," << y << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(WindowMoveEvent)
	};

	class WindowResizeEvent : public Event
	{
	public:
		explicit WindowResizeEvent(const int x, const int y) : x(x), y(y) { }
		const int x;
		const int y;

		EventType GetType() const override { return EventType::WindowResize; }
		EventCategory GetCategory() const override { return EventCategory::Window; }
		std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowResizeEvent(" << x << "," << y << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(WindowResizeEvent)
	};

	class WindowMaximizeEvent : public Event
	{
	public:
		explicit WindowMaximizeEvent(const bool maximized) : maximized(maximized) { }
		const bool maximized;

		EventType GetType() const override { return EventType::WindowMaximize; }
		EventCategory GetCategory() const override { return EventCategory::Window; }
		std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowMaximizeEvent(" << (maximized ? "true" : "false") << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(WindowMaximizeEvent)
	};

	class WindowFocusEvent : public Event
	{
	public:
		explicit WindowFocusEvent(const bool focused) : focused(focused) { }
		const bool focused;

		EventType GetType() const override { return EventType::WindowFocus; }
		EventCategory GetCategory() const override { return EventCategory::Window; }
		std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowFocusEvent(" << (focused ? "true" : "false") << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(WindowFocusEvent)
	};
}
