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
		JMath::iVec2 restorePos{ -1, -1 };
		JMath::iVec2 restoreSize{ -1, -1 };
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

		JMath::iVec2 GetPosition() const override;
		void SetPosition(JMath::iVec2 position);

		JMath::iVec2 GetSize() const override;
		void SetSize(JMath::iVec2 size) override;

		JMath::uiVec2 GetFramebufferSize() const override;

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
