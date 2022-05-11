#pragma once
#include <queue>
#include <vector>

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

		KeyboardKeyDown,
		KeyboardKeyUp
	};

	class JE_API_IO Event
	{
	public:
		virtual ~Event() {  }

		[[nodiscard]] virtual EventType GetType() const = 0;
		[[nodiscard]] virtual EventCategory GetCategory() const = 0;
		[[nodiscard]] virtual const char* ToString() const = 0;

	protected:
		Event() = default;
	};

	class JE_API_IO EventSystem
	{
	public:
		static void Subscribe(bool (*callback)(const Event* e));
		static void Trigger(const std::shared_ptr<Event> e);
		static void TriggerImmediate(const std::shared_ptr<Event> e);

	private:
		static std::vector<bool (*)(const Event*)> subscribers;
		static std::queue<std::shared_ptr<Event>> eventQueue;

		static void Dispatch(const Event* e);
	};
}
