#include "juniapch.hpp"
#include "EventSystem.hpp"

namespace Junia
{
	std::vector<bool (*)(const Event*)> EventSystem::subscribers;
	std::queue<Event*> EventSystem::eventQueue;

	void EventSystem::Subscribe(bool(* callback)(const Event* e))
	{
		subscribers.push_back(callback);
	}

	void EventSystem::Trigger(Event* e)
	{
		eventQueue.push(e);
	}

	void EventSystem::TriggerImmediate(const Event* e)
	{
		TriggerImmediate(e, true);
	}

	void EventSystem::TriggerImmediate(const Event* e, const bool deletePtr)
	{
		Dispatch(e);
		if (deletePtr) delete e;
	}

	void EventSystem::DispatchQueue()
	{
		for (unsigned long i = 0; i < eventQueue.size(); i++)
		{
			Dispatch(eventQueue.front());
			eventQueue.pop();
		}
	}

	void EventSystem::Dispatch(const Event* e)
	{
		for (bool(*callback)(const Event*) : subscribers) { if (callback(e)) break; }
	}
}
