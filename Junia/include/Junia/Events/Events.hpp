#pragma once

#include <deque>         // deque
#include <functional>    // function
#include <utility>       // pair
#include <cstddef>       // size_t
#include <string>        // string
#include <typeinfo>      // typeid
#include <typeindex>     // type_index
#include <unordered_map> // unordered_map

namespace Junia
{
	class Event
	{
	protected:
		Event() = default;

	public:
		virtual ~Event() = default;
		virtual std::string ToString() const;
	};

	namespace Internal
	{
		class EventSubscriberListContainer
		{
		public:
			virtual void Dispatch(const Event* e) = 0;
		};

		template<typename ET>
		class EventSubscriberList : public EventSubscriberListContainer
		{
		private:
			std::vector<std::function<void(const ET*)>> subscribers;

			void DispatchType(const ET* e)
			{
				for (size_t i = 0; i < subscribers.size(); i++) subscribers[i](e);
			}

		public:
			void Insert(std::function<void(const ET*)> handler)
			{
				subscribers.push_back(handler);
			}

			virtual void Dispatch(const Event* e) override
			{
				DispatchType(static_cast<const ET*>(e));
			}
		};
	}

	class Events
	{
	private:
		static std::deque<std::pair<Event*, std::type_index>> eventQueue;
		static std::unordered_map<std::type_index, Internal::EventSubscriberListContainer*> eventSubscribers;
		static std::vector<std::function<void(const Event*)>> subscribers;

		static void Dispatch(const Event* e);

	public:
		#define JE_EVENT_SUBSCRIBE_MEMBER(t,f) [this] (const t* e) { this->f(e); }

		/**
		 * @brief Register a function as an event callback to receive all events
		 * @param handler The callback function to register
		*/
		static void Subscribe(std::function<void(const Event*)> handler);

		/**
		 * @brief Dispatch all events that have been enqueued
		*/
		static void DispatchQueue();

		/**
		 * @brief Register a event type
		 * @tparam ET The type of the event to register
		*/
		template<typename ET>
		static void Register();

		/**
		 * @brief Register a function as an event callback to receive a certain
		 *        event type
		 * @tparam ET The type of event to receive
		 * @param handler The callback function to register
		*/
		template<typename ET>
		static void Subscribe(std::function<void(const ET*)> handler);

		/**
		 * @brief Trigger an event (enqueue it into to event queue; see
		 *        Events::DispatchQueue())
		 * @tparam ET The type of event to trigger
		 * @tparam ...ETArgs The types of the arguments to pass to the event
		 *                   constructor
		 * @param ...args The arguments to pass to the event constructor
		*/
		template<typename ET, typename... ETArgs>
		static void Trigger(ETArgs ...args);

		/**
		 * @brief Trigger an event
		 * @tparam ET The type of event to trigger
		 * @tparam ...ETArgs The types of the arguments to pass to the event
		 *                   constructor
		 * @param ...args The arguments to pass to the event constructor
		*/
		template<typename ET, typename... ETArgs>
		static void TriggerImmediate(ETArgs ...args);
	};

// ---------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------------- Events ------------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------

	template<typename ET>
	void Events::Register()
	{
		eventSubscribers.insert({ typeid(ET), new Internal::EventSubscriberList<ET>() });
	}

	template<typename ET>
	void Events::Subscribe(std::function<void(const ET*)> handler)
	{
		dynamic_cast<Internal::EventSubscriberList<ET>*>(eventSubscribers[typeid(ET)])->Insert(handler);
	}

	template<typename ET, typename... ETArgs>
	void Events::Trigger(ETArgs ...args)
	{
		eventQueue.push_back({ new ET(args...), typeid(ET) });
	}

	template<typename ET, typename... ETArgs>
	void Events::TriggerImmediate(ETArgs ...args)
	{
		Event* e = new ET(args...);
		eventSubscribers[typeid(ET)]->Dispatch(e);
		for (auto const& callback : subscribers)
			callback(e);
	}
}
