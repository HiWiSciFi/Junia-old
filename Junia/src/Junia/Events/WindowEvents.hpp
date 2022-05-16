#pragma once

#include "Event.hpp"

namespace Junia
{
	class WindowCloseEvent : public Event
	{
	public:
		explicit WindowCloseEvent() = default;

		[[nodiscard]] EventType GetType() const override { return EventType::WindowClose; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Window; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowCloseEvent()"); }
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
	};

	class WindowMaximizeEvent : public Event
	{
	public:
		explicit WindowMaximizeEvent(const bool maximized) : maximized(maximized) { }
		const bool maximized;

		[[nodiscard]] EventType GetType() const override { return EventType::WindowMaximize; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Window; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowMaximizeEvent(" << (maximized ? "true" : "false") << ")"); }
	};

	class WindowFocusEvent : public Event
	{
	public:
		explicit WindowFocusEvent(const bool focused) : focused(focused) { }
		const bool focused;

		[[nodiscard]] EventType GetType() const override { return EventType::WindowFocus; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Window; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowFocusEvent(" << (focused ? "true" : "false") << ")"); }
	};
}
