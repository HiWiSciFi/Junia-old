#include "EventSystem.hpp"

namespace Junia
{
	std::vector<std::function<bool(const Event*)>> EventSystem::subscribers;
	std::deque<Event*> EventSystem::eventQueue;

	void EventSystem::Subscribe(const std::function<bool(const Event*)>& callback)
	{
		subscribers.push_back(callback);
	}

	void EventSystem::Trigger(Event* e)
	{
		eventQueue.push_back(e);
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
			eventQueue.pop_front();
		}
	}

	void EventSystem::Dispatch(const Event* e)
	{
		for (const std::function<bool(const Event*)>& callback : subscribers) { if (callback(e)) break; }
	}
}
