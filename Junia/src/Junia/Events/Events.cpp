#include <Junia/Events/Events.hpp>

#include <sstream>

namespace Junia
{
	std::deque<std::pair<Event*, std::type_index>> Events::eventQueue{ };
	std::unordered_map<std::type_index, Internal::EventSubscriberListContainer*> Events::eventSubscribers{ };
	std::vector<std::function<void(const Event*)>> Events::subscribers{ };

	std::string Event::ToString() const
	{
		std::stringstream ss;
		ss << "Event";
		return ss.str();
	}

	void Events::Dispatch(const Event* e)
	{
		for (const auto& callback : subscribers) callback(e);
	}

	void Events::Subscribe(std::function<void(const Event*)> handler)
	{
		subscribers.push_back(handler);
	}

	void Events::DispatchQueue()
	{
		while (!eventQueue.empty())
		{
			auto& pair = eventQueue.back();
			eventSubscribers[pair.second]->Dispatch(pair.first);
			Dispatch(pair.first);
			eventQueue.pop_back();
		}
	}
}
