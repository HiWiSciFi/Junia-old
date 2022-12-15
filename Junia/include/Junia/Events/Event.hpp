#pragma once

#include <cinttypes>
#include <string>

#include <Junia/Core/Keycodes.hpp>

namespace Junia
{
	using EventType = uint64_t;
	using EventCategory = uint64_t;

	#define EVENT_TYPE_CUSTOM 0x0

	class Event
	{
	public:
		virtual ~Event() = default;

		virtual EventType GetType() const = 0;
		virtual EventType GetCategory() const = 0;
		virtual std::string ToString() const = 0;

	protected:
		Event() = default;
	};

	class KeyboardKeyDownEvent : public Event
	{
	public:
		KeyboardKeyDownEvent(KeyCode keyCode) : keyCode(keyCode) { }

		virtual EventType GetType() const { return EVENT_TYPE_CUSTOM; }

	private:
		KeyCode keyCode;
	};
}
