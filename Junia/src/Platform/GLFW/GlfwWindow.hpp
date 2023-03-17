#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <Junia/Core/Window.hpp>
#include <Junia/Core/WindowApi.hpp>

namespace GLFW
{
	class GlfwWindow : public Junia::Window
	{
	private:
		GLFWwindow* window;
		std::string title;
		JMath::iVec2 restorePos{ -1, -1 };
		JMath::iVec2 restoreSize{ -1, -1 };

	public:
		GlfwWindow(const std::string& title, int width = 800, int height = 600);
		~GlfwWindow();

		void Update() override;
		void Close() override;

		void* GetNative() const override;

		bool IsShown() const override;
		void Show() override;

		void Hide() override;

		const std::string& GetTitle() const override;
		void SetTitle(const std::string& title) override;

		JMath::iVec2 GetPosition() const override;
		void SetPosition(JMath::iVec2 position);

		JMath::iVec2 GetSize() const override;
		void SetSize(JMath::iVec2 size) override;

		float GetOpacity() const override;
		void SetOpacity(float opacity) override;

		bool IsFocused() const override;
		void RequestFocus() override;

		void RequestAttention() override;

		Junia::WindowSizeMode GetSizeMode() const override;
		void SetSizeMode(Junia::WindowSizeMode mode) override;

		Junia::WindowFullscreenMode GetFullscreenMode() const override;
		void SetFullscreenMode(Junia::WindowFullscreenMode mode, Junia::Monitor* monitor = nullptr) override;

	private:
		static void FramebufferResizeCallback(GLFWwindow* wnd, int width, int height);
	};
}
