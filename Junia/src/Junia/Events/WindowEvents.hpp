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

		[[nodiscard]] EventType GetType() const override { return EventType::WindowMove; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Window; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowMoveEvent(" << x << "," << y << ")"); }

		[[nodiscard]] std::pair<int, int> GetWindowPos() const { return std::pair<int, int>(x, y); }
		[[nodiscard]] int GetWindowX() const { return x; }
		[[nodiscard]] int GetWindowY() const { return y; }

		private:
			const int x;
			const int y;

		JE_EVENT_FUNCS_IMPL_Q(WindowMoveEvent)
	};

	class WindowResizeEvent : public Event
	{
	public:
		explicit WindowResizeEvent(const int x, const int y) : x(x), y(y) { }

		[[nodiscard]] EventType GetType() const override { return EventType::WindowResize; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Window; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowResizeEvent(" << x << "," << y << ")"); }

		[[nodiscard]] std::pair<int, int> GetWindowSize() const { return std::pair<int, int>(x, y); }
		[[nodiscard]] int GetWidth() const { return x; }
		[[nodiscard]] int GetHeight() const { return y; }

	private:
		const int x;
		const int y;

		JE_EVENT_FUNCS_IMPL_Q(WindowResizeEvent)
	};

	class WindowMaximizeEvent : public Event
	{
	public:
		explicit WindowMaximizeEvent(const bool maximized) : maximized(maximized) { }

		[[nodiscard]] EventType GetType() const override { return EventType::WindowMaximize; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Window; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowMaximizeEvent(" << (maximized ? "true" : "false") << ")"); }

		[[nodiscard]] bool IsMaximized() const { return maximized; }

	private:
		const bool maximized;

		JE_EVENT_FUNCS_IMPL_Q(WindowMaximizeEvent)
	};

	class WindowFocusEvent : public Event
	{
	public:
		explicit WindowFocusEvent(const bool focused) : focused(focused) { }

		[[nodiscard]] EventType GetType() const override { return EventType::WindowFocus; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Window; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("WindowFocusEvent(" << (focused ? "true" : "false") << ")"); }

		[[nodiscard]] bool IsFocused() const { return focused; }

	private:
		const bool focused;

		JE_EVENT_FUNCS_IMPL_Q(WindowFocusEvent)
	};
}
