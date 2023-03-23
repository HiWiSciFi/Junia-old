#pragma once

#include "Events.hpp"
#include "../Core/Window.hpp"

namespace Junia
{
	class WindowClosedEvent : public Event
	{
	private:
		Window* window = nullptr;

	public:
		/**
		 * @brief Create a window closed event
		 * @param windowId A pointer to the window the close was triggered for
		*/
		WindowClosedEvent(Window* window);

		/**
		 * @brief Get the window the close was triggered for
		 * @return A pointer to the closed window
		*/
		Window* GetWindow() const;

		virtual std::string ToString() const override;
	};
}
