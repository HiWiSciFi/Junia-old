#include "JoystickEvents.hpp"

namespace Junia
{
	std::vector<std::function<bool(const JoystickConnectEvent&)>> JoystickConnectEvent::subscribers;
}
