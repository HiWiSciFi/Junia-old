#include "KeyboardEvents.hpp"

namespace Junia
{
	std::vector<std::function<bool(const KeyboardKeyCharEvent*)>> KeyboardKeyCharEvent::subscribers;
	std::vector<std::function<bool(const KeyboardKeyDownEvent*)>> KeyboardKeyDownEvent::subscribers;
	std::vector<std::function<bool(const KeyboardKeyRepeatEvent*)>> KeyboardKeyRepeatEvent::subscribers;
	std::vector<std::function<bool(const KeyboardKeyUpEvent*)>> KeyboardKeyUpEvent::subscribers;
}
