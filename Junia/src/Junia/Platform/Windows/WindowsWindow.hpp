#pragma once

#ifdef JE_TARGETPLATFORM_WINDOWS

#include <Junia/Core/Window.hpp>
#include <Junia/Platform/OpenGL/OpenGLRenderContext.hpp>
#include <unordered_map>

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

		static WindowsWindow* GetWindow(Win32_HWND handle) { return windowMap[handle]; }

		bool movingWindow = false;
		int movingWindowCursorOffsetX = 0;
		int movingWindowCursorOffsetY = 0;
		int resizeOffsetX = 0;
		int resizeOffsetY = 0;
		bool resizingWindow = false;
		bool resizingWindowLeft = false;
		bool resizingWindowRight = false;
		bool resizingWindowTop = false;
		bool resizingWindowBottom = false;

		static std::unordered_map<Win32_HWND, WindowsWindow*> windowMap;

	private:
		virtual void Close();

		Win32_HWND window = nullptr;
		Win32_HDC hdc = nullptr;
		OpenGLRenderContext* context = nullptr;

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

		WindowData data { };
	};
}

#endif
