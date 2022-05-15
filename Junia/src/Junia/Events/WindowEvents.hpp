#pragma once

#include "Event.hpp"

namespace Junia
{
	class WindowMoveEvent : public Event
	{
	public:
		explicit WindowMoveEvent(const int x, const int y) : x(x), y(y) { }
		const int x, y;

		[[nodiscard]] EventType GetType() const override { return EventType::WindowMove; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Window; }
		[[nodiscard]] const char* ToString() const override { return "WindowMoveEvent"; }
	};

	class WindowResizeEvent : public Event
	{
	public:
		explicit WindowResizeEvent(const int x, const int y) : x(x), y(y) { }
		const int x, y;

		[[nodiscard]] EventType GetType() const override { return EventType::WindowResize; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Window; }
		[[nodiscard]] const char* ToString() const override { return "WindowResizeEvent"; }
	};
}
