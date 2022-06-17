#pragma once

#include <Junia/Window.hpp>
#include <Windows.h>

namespace Junia
{
	class WindowsWindow : public Window
	{
	public:
		explicit WindowsWindow(const WindowProperties& properties);
		~WindowsWindow() override;

		void OnUpdate() override;

		[[nodiscard]] unsigned int GetWidth() const override { return data.width; }
		[[nodiscard]] unsigned int GetHeight() const override { return data.height; }

		void SetVSync(bool enable) override;
		[[nodiscard]] bool IsVSync() const override;

		[[nodiscard]] void* GetNativeWindow() const override { return window; }

	private:
		virtual void Close();

		HWND* window;

		struct WindowData
		{
			std::string title;
			unsigned int width;
			unsigned int height;
			bool vSync;

			explicit WindowData(std::string title = "Junia Window", const unsigned int width = 960, const unsigned int height = 540, const bool vSync = true)
				: title(std::move(title)), width(width), height(height), vSync(vSync)
			{
			}
		};

		WindowData data;
	};
}
