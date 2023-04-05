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
		explicit WindowClosedEvent(Window* window);

		/**
		 * @brief Get the window the close was triggered for
		 * @return A pointer to the closed window
		*/
		[[nodiscard]] Window* GetWindow() const;

		[[nodiscard]] std::string ToString() const override;
	};
} // namespace Junia
