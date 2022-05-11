#pragma once
#include "Events.hpp"

namespace Junia
{
	class JE_API_IO KeyboardKeyDownEvent : public Event
	{
	public:
		explicit KeyboardKeyDownEvent(const int key) : key(key) { }
		const int key;

		[[nodiscard]] EventType GetType() const override { return EventType::KeyboardKeyDown; }
		[[nodiscard]] EventCategory GetCategory() const override { return EventCategory::Input; }
		[[nodiscard]] std::string ToString() const override { return "KeyboardKeyDownEvent"; }
	};
}
