#pragma once
#include "Event.hpp"

namespace Junia
{
	class JoystickConnectEvent : public Event
	{
	public:
		explicit JoystickConnectEvent(const int id, const bool maximized) : id(id), maximized(maximized) { }
		const int id;
		const bool maximized;

		[[nodiscard]] EventType GetType() const override { return EventType::JoystickConnect; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] const char* ToString() const override { return "JoystickConnectEvent"; }
	};
}
