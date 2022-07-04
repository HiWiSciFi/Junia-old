#include "MouseEvents.hpp"

namespace Junia
{
	std::vector<std::function<bool(const MouseButtonDownEvent&)>> MouseButtonDownEvent::subscribers;
	std::vector<std::function<bool(const   MouseButtonUpEvent&)>>   MouseButtonUpEvent::subscribers;
	std::vector<std::function<bool(const       MouseMoveEvent&)>>       MouseMoveEvent::subscribers;
	std::vector<std::function<bool(const     MouseScrollEvent&)>>     MouseScrollEvent::subscribers;
}
