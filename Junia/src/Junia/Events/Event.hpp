#pragma once

#include <sstream>
#include <vector>
#include <functional>

namespace Junia
{
	enum class EventCategory
	{
		Input,
		Window
	};

	enum class EventType
	{
		MouseMove,
		MouseButtonDown,
		MouseButtonUp,
		MouseScroll,

		KeyboardKeyDown,
		KeyboardKeyRepeat,
		KeyboardKeyUp,
		KeyboardKeyChar,

		JoystickConnect,

		WindowClose,
		WindowMove,
		WindowResize,
		WindowMaximize,
		WindowFocus
	};

#define JE_EVENT_TOSTR_MCR(x) std::stringstream ss; ss << ##x; return ss.str()
#define JE_EVENT_FUNCS_IMPL_Q(x) public: \
									static void Subscribe(std::function<bool(const x*)> callback) { subscribers.push_back(callback); } \
									static void Dispatch(const x* e) { for (auto f : subscribers) if (f(e)) break; } \
								private: \
									static std::vector<std::function<bool(const x*)>> subscribers;

	class Event
	{
	public:
		virtual ~Event() = default;

		[[nodiscard]] virtual EventType GetType() const = 0;
		[[nodiscard]] virtual EventCategory GetCategory() const = 0;
		[[nodiscard]] virtual std::string ToString() const = 0;

	protected:
		Event() = default;
	};
}
