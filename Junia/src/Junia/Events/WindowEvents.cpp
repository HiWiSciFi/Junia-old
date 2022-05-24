#include "WindowEvents.hpp"

namespace Junia
{
	std::vector<std::function<bool(const WindowCloseEvent*)>> WindowCloseEvent::subscribers;
	std::vector<std::function<bool(const WindowFocusEvent*)>> WindowFocusEvent::subscribers;
	std::vector<std::function<bool(const WindowMaximizeEvent*)>> WindowMaximizeEvent::subscribers;
	std::vector<std::function<bool(const WindowMoveEvent*)>> WindowMoveEvent::subscribers;
	std::vector<std::function<bool(const WindowResizeEvent*)>> WindowResizeEvent::subscribers;
}
