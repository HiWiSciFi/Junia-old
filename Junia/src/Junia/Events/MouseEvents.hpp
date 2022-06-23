#pragma once

#include <functional>
#include <Junia/Events/Event.hpp>

namespace Junia
{
	class MouseMoveEvent : public Event
	{
	public:
		explicit MouseMoveEvent(const float x, const float y) : x(x), y(y) { }

		[[nodiscard]] EventType GetType() const override { return EventType::MouseMove; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("MouseMoveEvent(" << x << "," << y << ")"); }

		[[nodiscard]] std::pair<float, float> GetMousePos() const { return std::pair<float, float>(x, y); }
		[[nodiscard]] float GetMouseX() const { return x; }
		[[nodiscard]] float GetMouseY() const { return y; }

	private:
		const float x;
		const float y;

		JE_EVENT_FUNCS_IMPL_Q(MouseMoveEvent)
	};

	class MouseButtonDownEvent : public Event
	{
	public:
		explicit MouseButtonDownEvent(const int button) : button(button) { }

		[[nodiscard]] EventType GetType() const override { return EventType::MouseButtonDown; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("MouseButtonDownEvent(" << button << ")"); }

		[[nodiscard]] int GetButton() const { return button; }

	private:
		const int button;

		JE_EVENT_FUNCS_IMPL_Q(MouseButtonDownEvent)
	};

	class MouseButtonUpEvent : public Event
	{
	public:
		explicit MouseButtonUpEvent(const int button) : button(button) { }

		[[nodiscard]] EventType GetType() const override { return EventType::MouseButtonUp; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("MouseButtonUpEvent(" << button << ")"); }

		[[nodiscard]] int GetButton() const { return button; }

	private:
		const int button;

		JE_EVENT_FUNCS_IMPL_Q(MouseButtonUpEvent)
	};

	class MouseScrollEvent : public Event
	{
	public:
		explicit MouseScrollEvent(const float xOffset, const float yOffset) : xOffset(xOffset), yOffset(yOffset) { }

		[[nodiscard]] EventType GetType() const override { return EventType::MouseScroll; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("MouseScrollEvent(" << xOffset << "," << yOffset << ")"); }

		[[nodiscard]] std::pair<float, float> GetOffset() const { return std::pair<float, float>(xOffset, yOffset); }
		[[nodiscard]] float GetXOffset() const { return xOffset; }
		[[nodiscard]] float GetYOffset() const { return yOffset; }

	private:
		const float xOffset;
		const float yOffset;

		JE_EVENT_FUNCS_IMPL_Q(MouseScrollEvent)
	};
}
