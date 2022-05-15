#pragma once

#include "Junia/Base.hpp"

#include <queue>
#include "Event.hpp"

namespace Junia
{
	class JE_API_IO EventSystem
	{
	public:
		static void Subscribe(bool (*callback)(const Event* e));
		static void Trigger(Event* e);
		static void TriggerImmediate(const Event* e);
		static void TriggerImmediate(const Event* e, const bool deletePtr);
		static void DispatchQueue();

	private:
		static std::vector<bool (*)(const Event*)> subscribers;
		static std::queue<Event*> eventQueue;

		static void Dispatch(const Event* e);
	};
}
