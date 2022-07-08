#ifdef JE_TARGETPLATFORM_WINDOWS

#include "WindowsWindow.hpp"

#include <Junia/Platform/Windows/Win32.hpp>

#include <Junia/Events/EventSystem.hpp>
#include <Junia/Events/WindowEvents.hpp>
#include <Junia/Events/MouseEvents.hpp>
#include <Junia/Events/KeyboardEvents.hpp>
#include <Junia/Core/Log.hpp>
#include <Junia/Platform/Windows/WindowsInput.hpp>

#include <Junia/Core/Input.hpp>

namespace Junia
{
	std::unordered_map<Win32_HWND, WindowsWindow*> WindowsWindow::windowMap;

	Window* Window::Create(const WindowProperties& properties)
	{
		WindowsInput::PopulateConversionArrays();
		return new WindowsWindow(properties);
	}

	long long WIN32_CALLBACK WndProc(Win32_HWND window, unsigned int msg, unsigned long long wp, long long lp)
	{
		 if (WindowsWindow::windowMap.find(window) == WindowsWindow::windowMap.end())
			return Win32_DefWindowProc(window, msg, wp, lp);
		// Helpful webpage: https://wiki.winehq.org/List_Of_Windows_Messages
		switch (msg)
		{
		// API Reference: https://docs.microsoft.com/en-us/windows/win32/menurc/wm-syscommand
		case WIN32_WM_SYSCOMMAND:
		{
			wp &= 0xFFF0;
			switch (wp)
			{
			case WIN32_SC_CLOSE: EventSystem::Trigger(new WindowCloseEvent()); break;
			case WIN32_SC_MAXIMIZE: Win32_ShowWindow(window, WIN32_SW_MAXIMIZE); break;
			case WIN32_SC_MINIMIZE: Win32_ShowWindow(window, WIN32_SW_MINIMIZE); break;
			case WIN32_SC_RESTORE: Win32_ShowWindow(window, WIN32_SW_RESTORE); break;
			case WIN32_SC_MOVE:
			{
				WindowsWindow* wnd = WindowsWindow::GetWindow(window);
				wnd->movingWindow = true;
				Win32_RECT rect;
				Win32_GetWindowRect(window, &rect);
				Win32_ShowWindow(window, WIN32_SW_RESTORE);
				// (rect.right - rect.left) / 2
				wnd->movingWindowCursorOffsetX = Win32_Get_X_LPARAM(lp) - rect.left;
				wnd->movingWindowCursorOffsetY = Win32_Get_Y_LPARAM(lp) - rect.top;
				break;
			}
			case WIN32_SC_SIZE:
			{
				WindowsWindow* wnd = WindowsWindow::GetWindow(window);
				wnd->resizingWindow = true;
				Win32_RECT rect;
				Win32_GetWindowRect(window, &rect);
				const int mouseX = Input::GetMouseX();
				const int mouseY = Input::GetMouseY();
				const int offset = static_cast<int>(static_cast<float>(Win32_GetDpiForSystem()) / 4.0f);
				wnd->resizingWindowLeft = mouseX < rect.left + offset && mouseX > rect.left - offset;
				wnd->resizingWindowRight = !wnd->resizingWindowLeft && mouseX < rect.right + offset && mouseX > rect.right - offset;
				wnd->resizingWindowBottom = mouseY < rect.bottom + offset && mouseY > rect.bottom - offset;
				wnd->resizingWindowTop = !wnd->resizingWindowBottom && mouseY < rect.top + offset && mouseY > rect.top - offset;
				break;
			}
			default: return Win32_DefWindowProc(window, msg, wp, lp);
			}
			return 0L;
		}

		// API Reference: https://docs.microsoft.com/en-us/windows/win32/winmsg/window-notifications
		case WIN32_WM_CLOSE:
		case WIN32_WM_DESTROY: EventSystem::Trigger(new WindowCloseEvent()); return 0L;

		case WIN32_WM_SIZE:
		{
			Win32_RECT rect;
			Win32_GetWindowRect(window, &rect);
			EventSystem::Trigger(new WindowResizeEvent(rect.right - rect.left, rect.bottom - rect.top));
			EventSystem::Trigger(new WindowMaximizeEvent(wp == 2));
			return 0L;
		}
		case WIN32_WM_MOVE: EventSystem::Trigger(new WindowMoveEvent(Win32_Get_X_LPARAM(lp), Win32_Get_Y_LPARAM(lp))); return 0L;
		case WIN32_WM_SIZING:
		{
			const auto rect = reinterpret_cast<Win32_LPRECT>(lp);
			EventSystem::Trigger(new WindowResizeEvent(rect->right - rect->left, rect->bottom - rect->top));
			return 0L;
		}
		// TODO: WindowFocusEvent

		// API Reference: https://docs.microsoft.com/en-us/windows/win32/inputdev/mouse-input
		case WIN32_WM_LBUTTONDOWN: EventSystem::Trigger(new MouseButtonDownEvent(0)); break;
		case WIN32_WM_LBUTTONUP:   EventSystem::Trigger(new MouseButtonUpEvent(0));   break;
		case WIN32_WM_RBUTTONDOWN: EventSystem::Trigger(new MouseButtonDownEvent(1)); break;
		case WIN32_WM_RBUTTONUP:   EventSystem::Trigger(new MouseButtonUpEvent(1));   break;
		case WIN32_WM_MBUTTONDOWN: EventSystem::Trigger(new MouseButtonDownEvent(2)); break;
		case WIN32_WM_MBUTTONUP:   EventSystem::Trigger(new MouseButtonUpEvent(2));   break;
		case WIN32_WM_MOUSEHWHEEL: EventSystem::Trigger(new MouseScrollEvent(static_cast<float>(Win32_Get_Wheel_Delta_WPARAM(wp)) / WIN32_WHEEL_DELTA, 0)); return 0L;
		case WIN32_WM_MOUSEWHEEL:  EventSystem::Trigger(new MouseScrollEvent(0, static_cast<float>(Win32_Get_Wheel_Delta_WPARAM(wp)) / WIN32_WHEEL_DELTA)); return 0L;
		case WIN32_WM_MOUSEMOVE:   EventSystem::Trigger(new MouseMoveEvent(static_cast<float>(Win32_Get_X_LPARAM(lp)), static_cast<float>(Win32_Get_Y_LPARAM(lp)))); break;

		// API Reference: https://docs.microsoft.com/en-us/windows/win32/inputdev/keyboard-input <-- Cool other stuff too : refer to Junia::WindowsInput
		case WIN32_WM_KEYDOWN: EventSystem::Trigger(new KeyboardKeyDownEvent(Junia::WindowsInput::WinToJeKey[static_cast<int>(wp)])); break;
		case WIN32_WM_KEYUP:   EventSystem::Trigger(new KeyboardKeyUpEvent(Junia::WindowsInput::WinToJeKey[static_cast<int>(wp)]));   break;
		case WIN32_WM_CHAR:    EventSystem::Trigger(new KeyboardKeyCharEvent(static_cast<int>(static_cast<unsigned int>(wp)))); break;

		// API Reference: https://docs.microsoft.com/en-us/windows/win32/inputdev/raw-input
		// TODO: implement Raw Input (Touch, Controllers, microphones, etc.)
		// TODO: JoystickConnectEvent
		}
		return Win32_DefWindowProc(window, msg, wp, lp);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		static bool isDpiAwarenessSet = Win32_SetProcessDpiAwarenessContext(WIN32_DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
		JELOG_BASE_ASSERT(isDpiAwarenessSet, "DPI Awareness is not set! Defaulted to 96 DPI");

		const auto titleWstr = std::wstring(properties.title.begin(), properties.title.end());
		const wchar_t* className = titleWstr.c_str();

		Win32_WNDCLASSEX wndclass{ };
		wndclass.cbSize = sizeof(Win32_WNDCLASSEX);
		wndclass.style = WIN32_CS_HREDRAW | WIN32_CS_VREDRAW | WIN32_CS_OWNDC;
		wndclass.lpfnWndProc = WndProc;
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = Win32_GetModuleHandle(nullptr);
		wndclass.hIcon = Win32_LoadIcon(nullptr, WIN32_IDI_APPLICATION);
		wndclass.hCursor = Win32_LoadCursor(nullptr, WIN32_IDC_ARROW);
		wndclass.hbrBackground = reinterpret_cast<Win32_HBRUSH>(WIN32_COLOR_BTNFACE + 1);
		wndclass.lpszMenuName = nullptr;
		wndclass.lpszClassName = className;
		wndclass.hIconSm = Win32_LoadIcon(nullptr, WIN32_IDI_APPLICATION);

		if (!Win32_RegisterClassEx(&wndclass))
		{
			JELOG_BASE_CRIT("Could not register window!");
			throw std::runtime_error("Could not register window!");
		}

		window = Win32_CreateWindowEx(0, wndclass.lpszClassName, className,
			WIN32_WS_OVERLAPPED | WIN32_WS_CAPTION | WIN32_WS_SYSMENU | WIN32_WS_MINIMIZEBOX | WIN32_WS_MAXIMIZEBOX | WIN32_WS_THICKFRAME,
			WIN32_CW_USEDEFAULT, WIN32_CW_USEDEFAULT,
			static_cast<int>(properties.width), static_cast<int>(properties.height),
			nullptr,
			nullptr,
			Win32_GetModuleHandle(nullptr),
			nullptr
		);
		if (!window)
		{
			JELOG_BASE_CRIT("Could not create window!");
			throw std::runtime_error("Could not create window!");
		}
		hdc = Win32_GetDC(window);
		if (hdc == nullptr)
		{
			JELOG_BASE_CRIT("Could not retrieve DeviceContext!");
			throw std::runtime_error("Could not retrieve DeviceContext!");
		}

		Win32_PIXELFORMATDESCRIPTOR pfd{ };
		pfd.nSize = sizeof(Win32_PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = WIN32_PFD_DRAW_TO_WINDOW | WIN32_PFD_SUPPORT_OPENGL | WIN32_PFD_DOUBLEBUFFER;
		pfd.iPixelType = WIN32_PFD_TYPE_RGBA;
		pfd.cColorBits = 32;
		pfd.cDepthBits = 24;
		pfd.cStencilBits = 8;
		pfd.iLayerType = WIN32_PFD_MAIN_PLANE; // ignored - relevant only for older versions of OpenGL

		const int format = Win32_ChoosePixelFormat(hdc, &pfd);
		if (format == 0)
		{
			JELOG_BASE_CRIT("Could not find compatible pixel format! Win32 Error: " JELOG_CSTR, Win32_GetLastError());
			throw std::runtime_error("Could not find compatible pixel format!");
		}
		if (Win32_SetPixelFormat(hdc, format, &pfd) == false)
		{
			JELOG_BASE_CRIT("Could not set pixelFormat! Win32 Error: " JELOG_CSTR, Win32_GetLastError());
			throw std::runtime_error("Could not set pixelFormat!");
		}

		context = new OpenGLRenderContext(this);
		context->Init();

		Win32_ShowWindow(window, WIN32_SW_SHOWDEFAULT);

		windowMap[window] = this;
	}

	WindowsWindow::~WindowsWindow()
	{
		WindowsWindow::Close();
	}

	void WindowsWindow::OnUpdate()
	{
		if (movingWindow)
		{
			if (Input::IsMouseButtonDown(JE_MOUSEBUTTON_LEFT))
			{
				Win32_RECT rect;
				Win32_GetWindowRect(window, &rect);
				Win32_MoveWindow(
					window,
					static_cast<long>(Input::GetMouseX()) - movingWindowCursorOffsetX,
					static_cast<long>(Input::GetMouseY()) - movingWindowCursorOffsetY,
					rect.right - rect.left,
					rect.bottom - rect.top,
					false
				);
			} else movingWindow = false;
		}

		if (resizingWindow)
		{
			if (Input::IsMouseButtonDown(JE_MOUSEBUTTON_LEFT))
			{
				Win32_RECT rect;
				Win32_GetWindowRect(window, &rect);
				const int mouseX = Input::GetMouseX();
				const int mouseY = Input::GetMouseY();
				Win32_MoveWindow(
					window,
					resizingWindowLeft ? mouseX : rect.left,
					resizingWindowTop ? mouseY : rect.top,
					resizingWindowLeft ? rect.right - mouseX : (resizingWindowRight ? mouseX - rect.left : rect.right - rect.left),
					resizingWindowTop ? rect.bottom - mouseY : (resizingWindowBottom ? mouseY - rect.top : rect.bottom - rect.top),
					false
				);
				Win32_GetWindowRect(window, &rect);
				EventSystem::Trigger(new WindowResizeEvent(rect.right - rect.left, rect.bottom - rect.top));
			} else resizingWindow = false;
		}

		Win32_MSG msg;
		while (Win32_PeekMessage(&msg, window, 0, 0, WIN32_PM_REMOVE))
		{
			Win32_TranslateMessage(&msg);
			Win32_DispatchMessage(&msg);
		}
		context->ContextSwapBuffers();
	}

	void WindowsWindow::SetVSync(bool)
	{

	}

	bool WindowsWindow::IsVSync() const
	{
		return false;
	}

	void WindowsWindow::Close()
	{
		windowMap.erase(window);
		delete context;
	}
}

#endif
