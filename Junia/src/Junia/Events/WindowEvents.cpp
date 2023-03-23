#include <Junia/Events/WindowEvents.hpp>
#include <sstream>

namespace Junia
{

// ---------------------------------------------------------------------------------------------------------------------
// ------------------------------------------------- WindowClosedEvent -------------------------------------------------
// ---------------------------------------------------------------------------------------------------------------------
	WindowClosedEvent::WindowClosedEvent(Window* window) : window(window) { }
	Window* WindowClosedEvent::GetWindow() const { return window; }
	std::string WindowClosedEvent::ToString() const
	{
		std::stringstream ss;
		ss << "WindowClosedEvent(" << window->GetId() << ")";
		return ss.str();
	}
}
