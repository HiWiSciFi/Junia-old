#pragma once
#include <GLFW/glfw3.h>
#undef APIENTRY
#include <Junia/Window.hpp>

namespace Junia
{
	class GlfwWindow : public Window
	{
	public:
		explicit GlfwWindow(const WindowProperties& properties);
		virtual ~GlfwWindow();

		void OnUpdate() override;

		inline unsigned GetWidth() const override { return data.width; }
		inline unsigned GetHeight() const override { return data.height; }

		void SetVSync(bool enable) override;
		bool IsVSync() const override;

		inline virtual void* getNativeWindow() const { return window; }

	private:
		virtual void Close();

		GLFWwindow* window;

		struct WindowData
		{
			std::string title;
			unsigned int width;
			unsigned int height;
			bool vSync;

			explicit WindowData(std::string title = "Junia Window", const unsigned int width = 960, const unsigned int height = 540, const bool vSync = true)
				: title(std::move(title)), width(width), height(height), vSync(vSync)
			{ }
		};

		WindowData data;
	};
}
