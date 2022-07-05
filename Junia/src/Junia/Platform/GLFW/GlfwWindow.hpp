#pragma once

#ifdef JE_TARGETPLATFORM_GLFW

#include <GLFW/glfw3.h>
#include <Junia/Core/Window.hpp>
#include <Junia/Platform/OpenGL/OpenGLRenderContext.hpp>

namespace Junia
{
	class GlfwWindow : public Window
	{
	public:
		explicit GlfwWindow(const WindowProperties& properties);
		~GlfwWindow() override;

		void OnUpdate() override;

		[[nodiscard]] unsigned int GetWidth() const override { return data.width; }
		[[nodiscard]] unsigned int GetHeight() const override { return data.height; }

		void SetVSync(bool enable) override;
		[[nodiscard]] bool IsVSync() const override;

		[[nodiscard]] void* GetNativeWindow() const override { return window; }

	private:
		virtual void Close();

		GLFWwindow* window;
		OpenGLRenderContext* context;

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

#endif

