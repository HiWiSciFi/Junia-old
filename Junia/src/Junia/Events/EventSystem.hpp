#pragma once

#include <Junia/Events/Event.hpp>
#include <functional>
#include <queue>

namespace Junia
{
	class EventSystem
	{
	public:
		static void Subscribe(const std::function<bool(const Event*)>& callback);
		static void Trigger(Event* e);
		static void TriggerImmediate(const Event* e);
		static void TriggerImmediate(const Event* e, const bool deletePtr);
		static void DispatchQueue();

	private:
		static std::vector<std::function<bool(const Event*)>> subscribers;
		static std::deque<Event*> eventQueue;

		static void Dispatch(const Event* e);
	};
}
