#ifdef JE_TARGETPLATFORM_WINDOWS

#include "WindowsWindow.hpp"

#include <Junia/Events/EventSystem.hpp>
#include <Junia/Events/WindowEvents.hpp>
#include <Junia/Events/MouseEvents.hpp>
#include <Junia/Events/KeyboardEvents.hpp>
#include <windowsx.h>
#include <glad/glad.h>
#include <Junia/Log.hpp>
#include <Junia/KeyCodes.hpp>

namespace Junia
{
	Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
	}

	int WinToJeKey(int keyCode)
	{
		switch (keyCode)
		{
		case VK_LEFT:  return  JE_KEY_LEFT;
		case VK_UP:    return    JE_KEY_UP;
		case VK_RIGHT: return JE_KEY_RIGHT;
		case VK_DOWN:  return  JE_KEY_DOWN;
		default: return keyCode;
		}
	}

	LRESULT CALLBACK WndProc(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
		// API Reference: https://docs.microsoft.com/en-us/windows/win32/winmsg/window-notifications
		case WM_CLOSE:
		case WM_DESTROY: EventSystem::Trigger(new WindowCloseEvent()); return 0L;

		case WM_SIZE: EventSystem::Trigger(new WindowMaximizeEvent(wp == 2)); break;
		case WM_MOVE: EventSystem::Trigger(new WindowMoveEvent(GET_X_LPARAM(lp), GET_Y_LPARAM(lp))); break;
		// TODO: WindowFocusEvent
		case WM_SIZING:
			{RECT* r = reinterpret_cast<RECT*>(lp);
			EventSystem::Trigger(new WindowResizeEvent(r->right - r->left, r->bottom - r->top));
			break;}

		// API Reference: https://docs.microsoft.com/en-us/windows/win32/inputdev/mouse-input
		case WM_LBUTTONDOWN: EventSystem::Trigger(new MouseButtonDownEvent(0)); break;
		case WM_LBUTTONUP:   EventSystem::Trigger(new MouseButtonUpEvent(0));   break;
		case WM_RBUTTONDOWN: EventSystem::Trigger(new MouseButtonDownEvent(1)); break;
		case WM_RBUTTONUP:   EventSystem::Trigger(new MouseButtonUpEvent(1));   break;
		case WM_MBUTTONDOWN: EventSystem::Trigger(new MouseButtonDownEvent(2)); break;
		case WM_MBUTTONUP:   EventSystem::Trigger(new MouseButtonUpEvent(2));   break;
		case WM_MOUSEHWHEEL: EventSystem::Trigger(new MouseScrollEvent(static_cast<float>(GET_WHEEL_DELTA_WPARAM(wp) / WHEEL_DELTA), 0)); return 0L;
		case WM_MOUSEWHEEL:  EventSystem::Trigger(new MouseScrollEvent(0, static_cast<float>(GET_WHEEL_DELTA_WPARAM(wp) / WHEEL_DELTA))); return 0L;
		case WM_MOUSEMOVE:   EventSystem::Trigger(new MouseMoveEvent(static_cast<float>(GET_X_LPARAM(lp)), static_cast<float>(GET_Y_LPARAM(lp)))); break;

		// TODO: Use KeyCodes from <Junia/KeyCodes.hpp>
		// API Reference: https://docs.microsoft.com/en-us/windows/win32/inputdev/keyboard-input <-- Cool other stuff too : refer to Junia::WindowsInput
		case WM_KEYDOWN: EventSystem::Trigger(new KeyboardKeyDownEvent(WinToJeKey(static_cast<int>(wp)))); break;
		case WM_KEYUP:   EventSystem::Trigger(new KeyboardKeyUpEvent(WinToJeKey(static_cast<int>(wp))));   break;
		case WM_CHAR:    EventSystem::Trigger(new KeyboardKeyCharEvent(static_cast<int>(static_cast<unsigned int>(wp)))); break;

		// API Reference: https://docs.microsoft.com/en-us/windows/win32/inputdev/raw-input
		// TODO: implement Raw Input (Touch, Controllers, microphones, etc.)
		// TODO: JoystickConnectEvent
		}
		return DefWindowProc(window, msg, wp, lp);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		std::wstring titleWstr = std::wstring(properties.title.begin(), properties.title.end());
		const wchar_t* className = titleWstr.c_str();

		WNDCLASSEX wndclass{ };
		wndclass.cbSize = sizeof(WNDCLASSEX);
		wndclass.style = 0;
		wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
		wndclass.lpfnWndProc = WndProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = GetModuleHandle(0);
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);
		wndclass.lpszMenuName = 0;
		wndclass.lpszClassName = className;

		if (!RegisterClassEx(&wndclass))
		{
			JELOG_BASE_CRIT("Could not register window!");
			throw std::runtime_error("Could not register window!");
		}

		window = CreateWindowEx(0, wndclass.lpszClassName, className,
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME,
			CW_USEDEFAULT, CW_USEDEFAULT, properties.width, properties.height, 0, 0, GetModuleHandle(0), 0);
		if (!window)
		{
			JELOG_BASE_CRIT("Could not create window!");
			throw std::runtime_error("Could not create window!");
		}
		hdc = GetDC(window);

		PIXELFORMATDESCRIPTOR pfd{ };
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.iLayerType = PFD_MAIN_PLANE;

		int format = ChoosePixelFormat(hdc, &pfd);
		if (format == 0)
		{
			JELOG_BASE_CRIT("Could not find compatible pixel format!");
			throw std::runtime_error("Could not find compatible pixel format!");
		}
		SetPixelFormat(hdc, format, &pfd);

		context = new OpenGLRenderContext(this);
		context->Init();

		ShowWindow(window, SW_SHOWDEFAULT);
		UpdateWindow(window);
	}

	WindowsWindow::~WindowsWindow()
	{
		Close();
	}

	void WindowsWindow::OnUpdate()
	{
		MSG msg;
		while (PeekMessage(&msg, window, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		context->ContextSwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enable)
	{

	}

	bool WindowsWindow::IsVSync() const
	{
		return false;
	}

	void WindowsWindow::Close()
	{
		delete context;
	}
}

#endif
