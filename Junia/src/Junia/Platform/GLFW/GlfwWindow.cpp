#include "GlfwWindow.hpp"

#include <Junia/Log.hpp>
#include <Junia/Events/EventSystem.hpp>
#include <Junia/Events/JoystickEvents.hpp>
#include <Junia/Events/KeyboardEvents.hpp>
#include <Junia/Events/MouseEvents.hpp>
#include <Junia/Events/WindowEvents.hpp>

namespace Junia
{
	static bool glfw_initialized = false;

	Window* Window::Create(const WindowProperties& properties)
	{
		return new GlfwWindow(properties);
	}

	GlfwWindow::GlfwWindow(const WindowProperties& properties)
	{
		data.title = properties.title;
		data.width = properties.width;
		data.height = properties.height;

		JELOG_BASE_INFO("Creating window {0} ({1}, {2})", properties.title, properties.width, properties.height);

		if (!glfw_initialized)
		{
			// TODO: glfwTerminate on system shutdown
			if (!glfwInit()) JELOG_BASE_CRIT("GLFW could not be initialized!");
			glfwSetErrorCallback([ ] (const int errorcode, const char* description)
				{
					JELOG_BASE_ERROR("GLFW Error ({0}) : {1}", errorcode, description);
				});
			glfw_initialized = true;
		}

		window = glfwCreateWindow(static_cast<int>(properties.width), static_cast<int>(properties.height), data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		// gladLoadGL();
		glfwSetWindowUserPointer(window, &data);
		GlfwWindow::SetVSync(true);

		// Window Callback

		glfwSetWindowSizeCallback(window, [ ] (GLFWwindow* w, const int width, const int height)
			{
				WindowData& wd = *static_cast<WindowData*>(glfwGetWindowUserPointer(w));
				wd.width = width;
				wd.height = height;
				EventSystem::Trigger(new WindowResizeEvent(width, height));
			});

		glfwSetWindowPosCallback(window, [](GLFWwindow* w, const int xPos, const int yPos)
			{
				EventSystem::Trigger(new WindowMoveEvent(xPos, yPos));
			});

		glfwSetWindowMaximizeCallback(window, [](GLFWwindow* _, const int maximized)
			{
				EventSystem::Trigger(new WindowMaximizeEvent(maximized == GLFW_TRUE ? true : false));
			});

		glfwSetWindowFocusCallback(window, [](GLFWwindow* w, const int focused)
			{
				EventSystem::Trigger(new WindowFocusEvent(focused == GLFW_TRUE ? true : false));
			});

		glfwSetWindowCloseCallback(window, [ ] (GLFWwindow* _)
			{
				EventSystem::Trigger(new WindowCloseEvent());
			});

		// Keyboard Callback

		glfwSetKeyCallback(window, [ ] (GLFWwindow* _, const int key, int scancode, const int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
					EventSystem::Trigger(new KeyboardKeyDownEvent(key));
					break;
				case GLFW_RELEASE:
					EventSystem::Trigger(new KeyboardKeyUpEvent(key));
					break;
				case GLFW_REPEAT:
					EventSystem::Trigger(new KeyboardKeyRepeatEvent(key));
					break;
				default:
					break;
				}
			});

		glfwSetCharCallback(window, [] (GLFWwindow* w, unsigned int codepoint)
			{
				EventSystem::Trigger(new KeyboardKeyCharEvent(codepoint));
			});

		// Mouse Callback

		glfwSetMouseButtonCallback(window, [ ] (GLFWwindow* w, const int button, const int action, int mods)
			{
				switch (action)
				{
				case GLFW_PRESS:
					EventSystem::Trigger(new MouseButtonDownEvent(button));
					break;
				case GLFW_RELEASE:
					EventSystem::Trigger(new MouseButtonUpEvent(button));
					break;
				default:
					break;
				}
			});

		glfwSetScrollCallback(window, [ ] (GLFWwindow* w, const double xOffset, const double yOffset)
			{
				EventSystem::Trigger(new MouseScrollEvent(static_cast<float>(xOffset), static_cast<float>(yOffset)));
			});

		glfwSetCursorPosCallback(window, [ ] (GLFWwindow* w, const double xPos, const double yPos)
			{
				EventSystem::Trigger(new MouseMoveEvent(static_cast<float>(xPos), static_cast<float>(yPos)));
			});

		// Joystick Callback

		glfwSetJoystickCallback([](const int jid, const int connected)
			{
				EventSystem::Trigger(new JoystickConnectEvent(jid, connected == GLFW_CONNECTED ? true : false));
			});
	}

	GlfwWindow::~GlfwWindow()
	{
		GlfwWindow::Close();
	}

	void GlfwWindow::Close()
	{
		glfwDestroyWindow(window);
	}

	void GlfwWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void GlfwWindow::SetVSync(const bool enable)
	{
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		data.vSync = enable;
	}

	bool GlfwWindow::IsVSync() const
	{
		return data.vSync;
	}
}
