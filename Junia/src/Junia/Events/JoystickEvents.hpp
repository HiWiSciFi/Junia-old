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

		EventType GetType() const override { return EventType::JoystickConnect; }
		EventCategory GetCategory() const override { return EventCategory::Input; }
		std::string ToString() const override { JE_EVENT_TOSTR_MCR("JoystickConnectEvent(" << id << "," << (connected ? "true" : "false") << ")"); }

		JE_EVENT_FUNCS_IMPL_Q(JoystickConnectEvent)
	};
}