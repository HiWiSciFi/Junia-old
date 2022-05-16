#pragma once
#include "Event.hpp"

namespace Junia
{
	class JoystickConnectEvent : public Event
	{
	public:
		explicit JoystickConnectEvent(const int id, const bool connected) : id(id), connected(connected) { }
		const int id;
		const bool connected;

		[[nodiscard]] EventType GetType() const override { return EventType::JoystickConnect; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("JoystickConnectEvent(" << id << "," << (connected ? "true" : "false") << ")"); }
	};
}
