#pragma once
#include "Window.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Junia
{
	class GlfwWindow : public Window
	{
	public:
		explicit GlfwWindow(const WindowProperties& properties);
		virtual ~GlfwWindow();

		void OnUpdate() override;

		[[nodiscard]] inline unsigned GetWidth() const override { return data.width; }
		[[nodiscard]] inline unsigned GetHeight() const override { return data.height; }

		void SetVSync(bool enable) override;
		[[nodiscard]] bool IsVSync() const override;

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
