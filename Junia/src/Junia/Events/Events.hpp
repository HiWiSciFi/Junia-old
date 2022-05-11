#pragma once
#include <queue>

namespace Junia
{
	enum class JE_API_IO EventCategory
	{
		Input,
		Window
	};

	enum class JE_API_IO EventType
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
		[[nodiscard]] virtual std::string ToString() const = 0;

	protected:
		Event() = default;
	};

	class JE_API_IO EventSystem
	{
	public:
		static void Subscribe(bool (*callback)(const Event* e));
		static void Trigger(Event* e);
		static void TriggerImmediate(const Event* e);

	private:
		static std::vector<bool (*)(const Event*)> subscribers;
		static std::queue<std::shared_ptr<Event>> eventQueue;

		static void Dispatch(const Event* e);
	};
}
