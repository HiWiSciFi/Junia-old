#include "EventSystem.hpp"
#include <Junia/Events/JoystickEvents.hpp>
#include <Junia/Events/KeyboardEvents.hpp>
#include <Junia/Events/MouseEvents.hpp>
#include <Junia/Events/WindowEvents.hpp>
#include <Junia/Log.hpp>

namespace Junia
{
	std::vector<std::function<bool(const Event&)>> EventSystem::subscribers;
	std::deque<Event*> EventSystem::eventQueue;

	void EventSystem::Subscribe(const std::function<bool(const Event&)>& callback)
	{
		subscribers.push_back(callback);
	}

	void EventSystem::Trigger(Event* e)
	{
		eventQueue.push_back(e);
	}

	void EventSystem::TriggerImmediate(const Event* e, bool deletePtr)
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

	#define JE_EVENT_DISPATCH_SWITCH_IMPL_Q(x)	case EventType:: ## x: \
												{ \
													const x ## Event* ev = static_cast<const x ## Event*>(e); \
													x ## Event::Dispatch(ev); \
													break; \
												}

	void EventSystem::Dispatch(const Event* e)
	{
		for (const std::function<bool(const Event&)>& callback : subscribers) { if (callback(*e)) return; }
		switch (e->GetType())
		{
			JE_EVENT_DISPATCH_SWITCH_IMPL_Q(JoystickConnect)

			JE_EVENT_DISPATCH_SWITCH_IMPL_Q(KeyboardKeyChar)
			JE_EVENT_DISPATCH_SWITCH_IMPL_Q(KeyboardKeyDown)
			JE_EVENT_DISPATCH_SWITCH_IMPL_Q(KeyboardKeyUp)

			JE_EVENT_DISPATCH_SWITCH_IMPL_Q(MouseButtonDown)
			JE_EVENT_DISPATCH_SWITCH_IMPL_Q(MouseButtonUp)
			JE_EVENT_DISPATCH_SWITCH_IMPL_Q(MouseMove)
			JE_EVENT_DISPATCH_SWITCH_IMPL_Q(MouseScroll)

			JE_EVENT_DISPATCH_SWITCH_IMPL_Q(WindowClose)
			JE_EVENT_DISPATCH_SWITCH_IMPL_Q(WindowFocus)
			JE_EVENT_DISPATCH_SWITCH_IMPL_Q(WindowMaximize)
			JE_EVENT_DISPATCH_SWITCH_IMPL_Q(WindowMove)
			JE_EVENT_DISPATCH_SWITCH_IMPL_Q(WindowResize)
		}
	}
}
