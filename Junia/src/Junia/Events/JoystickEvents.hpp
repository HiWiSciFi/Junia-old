#pragma once

#include <functional>
#include <Junia/Events/Event.hpp>

namespace Junia
{
	class JoystickConnectEvent : public Event
	{
	public:
		explicit JoystickConnectEvent(const int id, const bool connected) : id(id), connected(connected) { }

		[[nodiscard]] EventType GetType() const override { return EventType::JoystickConnect; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { JE_EVENT_TOSTR_MCR("JoystickConnectEvent(" << id << "," << (connected ? "true" : "false") << ")"); }

		[[nodiscard]] int GetID() const { return id; }
		[[nodiscard]] bool IsConnected() const { return connected; }

	private:
		const int id;
		const bool connected;

		//JE_EVENT_FUNCS_IMPL_Q(JoystickConnectEvent)
	public:
		static void Subscribe(std::function<bool(const JoystickConnectEvent&)> callback) { subscribers.push_back(callback); }
		static void Dispatch(const JoystickConnectEvent* e) { for (const auto& f : subscribers) if (f(*e)) break; }
	private:
		static std::vector<std::function<bool(const JoystickConnectEvent&)>> subscribers;
	};
}
