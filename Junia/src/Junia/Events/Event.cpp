#include <Junia/Events/Event.hpp>

namespace Junia
{
	std::deque<Event*> Events::eventQueue{ };
	std::unordered_map<std::type_index, EventSubscriberListContainer*> Events::eventSubscribers{ };
	std::vector<std::function<void(Event*)>> Events::subscribers{ };
}
