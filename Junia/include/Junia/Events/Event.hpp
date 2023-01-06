#pragma once

#include <cinttypes>
#include <string>
#include <sstream>
#include <deque>
#include <typeinfo>
#include <typeindex>
#include <functional>
#include <unordered_map>

#include <Junia/Core/Keycodes.hpp>

namespace Junia
{
	class Event
	{
	protected:
		Event() = default;

	public:
		virtual ~Event() = default;
	};

	class EventSubscriberListContainer
	{
	public:
		virtual void Dispatch(Event* e) = 0;
	};

	template<typename ET>
	class EventSubscriberList : public EventSubscriberListContainer
	{
	private:
		std::vector<std::function<void(ET*)>> subscribers;

		void DispatchType(ET* e)
		{
			for (size_t i = 0; i < subscribers.size(); i++) subscribers[i](e);
		}

	public:
		void Insert(std::function<void(ET*)> handler)
		{
			subscribers.push_back(handler);
		}

		virtual void Dispatch(Event* e) override
		{
			DispatchType(dynamic_cast<ET*>(e));
		}
	};

	class Events
	{
	private:
		static std::deque<Event*> eventQueue;
		static std::unordered_map<std::type_index, EventSubscriberListContainer*> eventSubscribers;
		static std::vector<std::function<void(Event*)>> subscribers;

		void Dispatch(Event* e)
		{
			for (size_t i = 0; i < subscribers.size(); i++) subscribers[i](e);
		}

	public:
		template<typename ET>
		static void Register()
		{
			eventSubscribers.insert({ typeid(ET), new EventSubscriberList<ET>() });
		}

		static void Subscribe(std::function<void(Event*)> handler)
		{
			subscribers.push_back(handler);
		}

		template<typename ET>
		static void Subscribe(std::function<void(ET*)> handler)
		{
			dynamic_cast<EventSubscriberList<ET>*>(eventSubscribers[typeid(ET)])->Insert(handler);
		}

		template<typename ET, typename... ETArgs>
		static void Trigger(ETArgs ...args)
		{
			eventQueue.push_back(new ET(args...));
		}

		template<typename ET, typename... ETArgs>
		static void TriggerImmediate(ETArgs ...args)
		{
			Event* e = new ET(args...);
			eventSubscribers[typeid(ET)]->Dispatch(e);
		}
	};



	class KeyDownEvent : public Event
	{
	private:
		KeyCode keyCode;

	public:
		KeyDownEvent(KeyCode keyCode) : keyCode(keyCode) { }
		KeyCode GetKeyCode() { return keyCode; }
	};
}
