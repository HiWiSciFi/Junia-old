#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#undef GLFW_INCLUDE_VULKAN
#include <Junia/Core/Window.hpp>
#include <memory>

namespace GLFW
{
	class GlfwWindow : public Junia::Window
	{
	private:
		GLFWwindow* window;
		std::string title;
		JMath::Vec2i restorePos{ -1, -1 };
		JMath::Vec2i restoreSize{ -1, -1 };
		std::shared_ptr<Junia::Scene> scene;

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

		JMath::Vec2i GetPosition() const override;
		void SetPosition(JMath::Vec2i position);

		JMath::Vec2i GetSize() const override;
		void SetSize(JMath::Vec2i size) override;

		JMath::Vec2ui GetFramebufferSize() const override;

		float GetOpacity() const override;
		void SetOpacity(float opacity) override;

		bool IsFocused() const override;
		void RequestFocus() override;

		void RequestAttention() override;

		Junia::WindowSizeMode GetSizeMode() const override;
		void SetSizeMode(Junia::WindowSizeMode mode) override;

		Junia::WindowFullscreenMode GetFullscreenMode() const override;
		void SetFullscreenMode(Junia::WindowFullscreenMode mode, Junia::Monitor* monitor = nullptr) override;

		void AttachScene(Junia::Scene::IdType sceneId) override;

	private:
		static void FramebufferResizeCallback(GLFWwindow* wnd, int width, int height);
	};
}
