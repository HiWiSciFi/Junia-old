#include "GlfwWindow.hpp"
#include <stdexcept>
#include <vector>
#include <Junia/Events/InputEvents.hpp>
#include "GlfwInput.hpp"

namespace Junia
{
	extern std::vector<Window*> windows;
}

namespace GLFW
{
	GlfwWindow::GlfwWindow(const std::string& title, int width, int height) : title(title)
	{
		id = -1;
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (window == NULL) throw std::runtime_error("failed to create window");
		glfwSetWindowUserPointer(window, this);

		glfwSetWindowFocusCallback(window, [] (GLFWwindow* window, int focused)
			{
				GlfwWindow* w = reinterpret_cast<GlfwWindow*>(glfwGetWindowUserPointer(window));
				Junia::windows[0] = focused ? w : (Junia::windows[0] == w ? nullptr : Junia::windows[0]);
			});

		id = static_cast<int>(Junia::windows.size());
		Junia::windows.push_back(this);
		if (Junia::windows[0] == nullptr) Junia::windows[0] = this;

		glfwSetKeyCallback(window, [ ] (GLFWwindow* _, const int key, int scancode, const int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
					Junia::Events::Trigger<Junia::KeyDownEvent>(static_cast<Junia::KeyCode>(GlfwToJeKey[key]));
					break;
				case GLFW_RELEASE:
					Junia::Events::Trigger<Junia::KeyUpEvent>(static_cast<Junia::KeyCode>(GlfwToJeKey[key]));
					break;
				default:
					break;
				}
			});

		glfwSetCharCallback(window, [ ] (GLFWwindow* window, unsigned int codepoint)
			{
				Junia::Events::Trigger<Junia::KeyCharEvent>(codepoint);
			});

		glfwSetMouseButtonCallback(window, [ ] (GLFWwindow* _, int button, int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
					Junia::Events::Trigger<Junia::MouseButtonDownEvent>(static_cast<Junia::MouseButton>(GlfwToJeButton[button]));
					break;
				case GLFW_RELEASE:
					Junia::Events::Trigger<Junia::MouseButtonUpEvent>(static_cast<Junia::MouseButton>(GlfwToJeButton[button]));
					break;
				default:
					break;
				}
			});

		glfwSetCursorPosCallback(window, [ ] (GLFWwindow* _, double xpos, double ypos)
			{
				Junia::Events::Trigger<Junia::MouseMoveEvent>(JMath::iVec2(static_cast<int>(xpos), static_cast<int>(ypos)));
			});

		surface = Junia::Surface::Create(window, Junia::WindowApi::GLFW, Junia::RenderApi::VULKAN);
	}

	GlfwWindow::~GlfwWindow()
	{
		delete surface;
		glfwDestroyWindow(window);
		if (Junia::windows[0] == this) Junia::windows[0] = nullptr;
		if (Junia::windows.size() >= 3) Junia::Window::SwapIds(id, static_cast<Junia::Window::IdType>(Junia::windows.size() - 1));
		Junia::windows.pop_back();
	}

	void GlfwWindow::Update()
	{
		if (!IsShown()) return;
		if (glfwWindowShouldClose(window))
		{
			delete this;
			return;
		}

		// draw
		surface->Draw();

		glfwPollEvents();
	}

	void GlfwWindow::Close()
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}

	void* GlfwWindow::GetNative() const
	{
		return window;
	}

	bool GlfwWindow::IsShown() const
	{
		return glfwGetWindowAttrib(window, GLFW_VISIBLE);
	}

	void GlfwWindow::Show()
	{
		if (IsShown()) return;
		glfwShowWindow(window);
	}

	void GlfwWindow::Hide()
	{
		if (!IsShown()) return;
		glfwHideWindow(window);
	}

	const std::string& GlfwWindow::GetTitle() const
	{
		return title;
	}

	void GlfwWindow::SetTitle(const std::string& title)
	{
		this->title = title;
		glfwSetWindowTitle(window, title.c_str());
	}

	JMath::iVec2 GlfwWindow::GetPosition() const
	{
		int x, y;
		glfwGetWindowPos(window, &x, &y);
		return { x, y };
	}

	void GlfwWindow::SetPosition(JMath::iVec2 position)
	{
		glfwSetWindowPos(window, position.x, position.y);
	}

	JMath::iVec2 GlfwWindow::GetSize() const
	{
		JMath::iVec2 size{ };
		glfwGetWindowSize(window, &size.x, &size.y);
		return size;
	}

	void GlfwWindow::SetSize(JMath::iVec2 size)
	{
		glfwSetWindowSize(window, size.x, size.y);
	}

	float GlfwWindow::GetOpacity() const
	{
		return glfwGetWindowOpacity(window);
	}

	void GlfwWindow::SetOpacity(float opacity)
	{
		glfwSetWindowOpacity(window, opacity);
	}

	bool GlfwWindow::IsFocused() const
	{
		return glfwGetWindowAttrib(window, GLFW_FOCUSED);
	}

	void GlfwWindow::RequestFocus()
	{
		glfwFocusWindow(window);
	}

	void GlfwWindow::RequestAttention()
	{
		glfwRequestWindowAttention(window);
	}

	Junia::WindowSizeMode GlfwWindow::GetSizeMode() const
	{
		if (glfwGetWindowAttrib(window, GLFW_MAXIMIZED) == GLFW_TRUE) return Junia::WindowSizeMode::MAXIMIZED;
		if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) == GLFW_TRUE) return Junia::WindowSizeMode::ICONIFIED;
		return Junia::WindowSizeMode::REGULAR;
	}

	void GlfwWindow::SetSizeMode(Junia::WindowSizeMode mode)
	{
		if (mode == GetSizeMode()) return;

		switch (mode)
		{
		case Junia::WindowSizeMode::REGULAR:    glfwRestoreWindow(window); break;
		case Junia::WindowSizeMode::ICONIFIED:  glfwIconifyWindow(window); break;
		case Junia::WindowSizeMode::MAXIMIZED: glfwMaximizeWindow(window); break;
		default: break;
		}
	}

	Junia::WindowFullscreenMode GlfwWindow::GetFullscreenMode() const
	{
		return Junia::WindowFullscreenMode::WINDOWED;
	}

	void GlfwWindow::SetFullscreenMode(Junia::WindowFullscreenMode mode)
	{
		return;
	}

	/*void GlfwWindow::Fullscreen()
	{
		int monitorCount;
		GLFWmonitor** monitors = glfwGetMonitors(&monitorCount);
		const GLFWvidmode* mode = glfwGetVideoMode(monitors[0]);

		glfwSetWindowMonitor(window, monitors[0], 0, 0, mode->width, mode->height, mode->refreshRate);
	}

	void GlfwWindow::Windowed()
	{
		glfwSetWindowMonitor(window, NULL, 100, 100, 800, 600, 0);
	}*/
}
