#include "juniapch.hpp"

#include "Events.hpp"

namespace Junia
{
	std::vector<bool (*)(const Event*)> EventSystem::subscribers;
	std::queue<std::shared_ptr<Event>> EventSystem::eventQueue;

	void EventSystem::Subscribe(bool(* callback)(const Event* e))
	{
		subscribers.push_back(callback);
	}

	void EventSystem::Trigger(const std::shared_ptr<Event> e)
	{
		eventQueue.push(e);
	}

	void EventSystem::TriggerImmediate(const std::shared_ptr<Event> e)
	{
		Dispatch(e.get());
	}

	void EventSystem::Dispatch(const Event* e)
	{
		for (bool(*callback)(const Event*) : subscribers) { if (callback(e)) break; }
	}
}
