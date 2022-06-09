#pragma once

#include <functional>
#include <Junia/Events/Event.hpp>

namespace Junia
{
	class WindowCloseEvent : public Event
	{
	public:
		explicit WindowCloseEvent() = default;

		[[nodiscard]] EventType GetType() const override { return EventType::WindowClose; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Window; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowCloseEvent()"); }

		JE_EVENT_FUNCS_IMPL_Q(WindowCloseEvent)
	};

	class WindowMoveEvent : public Event
	{
	public:
		explicit WindowMoveEvent(const int x, const int y) : x(x), y(y) { }
		const int x;
		const int y;

		[[nodiscard]] EventType GetType() const override { return EventType::WindowMove; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Window; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowMoveEvent(" << x << "," << y << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(WindowMoveEvent)
	};

	class WindowResizeEvent : public Event
	{
	public:
		explicit WindowResizeEvent(const int x, const int y) : x(x), y(y) { }
		const int x;
		const int y;

		[[nodiscard]] EventType GetType() const override { return EventType::WindowResize; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Window; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowResizeEvent(" << x << "," << y << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(WindowResizeEvent)
	};

	class WindowMaximizeEvent : public Event
	{
	public:
		explicit WindowMaximizeEvent(const bool maximized) : maximized(maximized) { }
		const bool maximized;

		[[nodiscard]] EventType GetType() const override { return EventType::WindowMaximize; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Window; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowMaximizeEvent(" << (maximized ? "true" : "false") << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(WindowMaximizeEvent)
	};

	class WindowFocusEvent : public Event
	{
	public:
		explicit WindowFocusEvent(const bool focused) : focused(focused) { }
		const bool focused;

		[[nodiscard]] EventType GetType() const override { return EventType::WindowFocus; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Window; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowFocusEvent(" << (focused ? "true" : "false") << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(WindowFocusEvent)
	};
}
