#pragma once
#include <string>

#include "Base.hpp"

namespace Junia
{
	struct WindowProperties
	{
		const std::string title;
		unsigned int width;
		unsigned int height;

		WindowProperties(std::string title = "Junia Window",
			const unsigned int width = 960,
			const unsigned int height = 540)
			: title(std::move(title)), width(width), height(height) { }
	};

	class JE_API_IO Window
	{
	public:
		virtual ~Window() = default;

		virtual void OnUpdate() = 0;

		[[nodiscard]] virtual unsigned int GetWidth() const = 0;
		[[nodiscard]] virtual unsigned int GetHeight() const = 0;

		virtual void SetVSync(bool enable) = 0;
		[[nodiscard]] virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}
