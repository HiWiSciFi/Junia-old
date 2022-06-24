#include "WindowsWindow.hpp"
#include <iostream>
#include <Junia/Events/EventSystem.hpp>
#include <Junia/Events/WindowEvents.hpp>
#include <Junia/Events/MouseEvents.hpp>
#include <Junia/Events/KeyboardEvents.hpp>
#include <windowsx.h>
#include <glad/glad.h>
#include <Junia/Log.hpp>

namespace Junia
{
	#define WGL_CONTEXT_MAJOR_VERSION_ARB 0x2091
	#define WGL_CONTEXT_MINOR_VERSION_ARB 0X2092
	#define WGL_CONTEXT_FLAGS_ARB 0X2094
	#define WGL_CONTEXT_COREPROFILE_BIT_ARB 0x00000001
	#define WGL_CONTEXT_PROFILE_MASK_ARB 0x9126
	typedef HGLRC(WINAPI* PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int* attribList);

	Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
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
		case WM_KEYDOWN: EventSystem::Trigger(new KeyboardKeyDownEvent(static_cast<int>(wp))); break;
		case WM_KEYUP: EventSystem::Trigger(new KeyboardKeyUpEvent(static_cast<int>(wp))); break;
		case WM_CHAR: EventSystem::Trigger(new KeyboardKeyCharEvent(static_cast<int>(static_cast<unsigned int>(wp)))); break;

		// API Reference: https://docs.microsoft.com/en-us/windows/win32/inputdev/raw-input
		// TODO: implement Raw Input (Touch, Controllers, microphones, etc.)
		}
		return DefWindowProc(window, msg, wp, lp);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		std::wstring titleWstr = std::wstring(properties.title.begin(), properties.title.end());
		const wchar_t* className = titleWstr.c_str();

		WNDCLASSEX  wndclass;
		wndclass.cbSize = sizeof(WNDCLASSEX);
		wndclass.style = 0;
		wndclass.style = CS_HREDRAW | CS_VREDRAW; // ACTIVATES RELOAD ON REDRAW
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

		if (!RegisterClassEx(&wndclass)) return;

		window = CreateWindowEx(0, wndclass.lpszClassName, className,
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_THICKFRAME,
			CW_USEDEFAULT, CW_USEDEFAULT, properties.width, properties.height, 0, 0, GetModuleHandle(0), 0);
		if (!window)
		{
			JELOG_BASE_ERROR("Could not create Window!");
			return;
		}
		hdc = GetDC(window);

		PIXELFORMATDESCRIPTOR pfd;
		memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));
		pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
		pfd.nVersion = 1;
		pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
		pfd.iPixelType = PFD_TYPE_RGBA;
		pfd.cColorBits = 24;

		pfd.cDepthBits = 32;
		pfd.cStencilBits = 8;

		int pixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, pixelFormat, &pfd);

		ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, 0, &pfd);

		HGLRC dummyctx = wglCreateContext(hdc);
		wglMakeCurrent(hdc, dummyctx);
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
		wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
		const int attribList[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
			WGL_CONTEXT_MINOR_VERSION_ARB, 3,
			WGL_CONTEXT_FLAGS_ARB, 0,
			WGL_CONTEXT_PROFILE_MASK_ARB,
			WGL_CONTEXT_COREPROFILE_BIT_ARB, 0,
		};
		ctx = wglCreateContextAttribsARB(hdc, 0, attribList);
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(dummyctx);
		wglMakeCurrent(hdc, ctx);

		int status = gladLoadGL();
		JELOG_BASE_INFO("GLAD loaded!");
		if (!status) JELOG_BASE_CRIT("failed to initialize glad! Errorcode: " JELOG_INT, status);

		ShowWindow(window, SW_SHOWDEFAULT);
		UpdateWindow(window);

		glClearColor(1.0f, 0.0f, .7f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
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
		SwapBuffers(hdc);
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
		wglMakeCurrent(hdc, ctx);
		wglDeleteContext(ctx);
	}
}
