#include "WindowsWindow.hpp"
#include <iostream>
#include <Junia/Events/EventSystem.hpp>
#include <Junia/Events/WindowEvents.hpp>
#include <Junia/Events/MouseEvents.hpp>
#include <windowsx.h>

namespace Junia
{
	Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
	}

	LRESULT CALLBACK WndProc(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
		case WM_DESTROY: EventSystem::Trigger(new WindowCloseEvent()); return 0L;


		case WM_LBUTTONDOWN: EventSystem::Trigger(new MouseButtonDownEvent(0)); break;
		case WM_LBUTTONUP:   EventSystem::Trigger(new MouseButtonUpEvent(0));   break;
		case WM_RBUTTONDOWN: EventSystem::Trigger(new MouseButtonDownEvent(1)); break;
		case WM_RBUTTONUP:   EventSystem::Trigger(new MouseButtonUpEvent(1));   break;
		case WM_MBUTTONDOWN: EventSystem::Trigger(new MouseButtonDownEvent(2)); break;
		case WM_MBUTTONUP:   EventSystem::Trigger(new MouseButtonUpEvent(2));   break;
		case WM_MOUSEWHEEL:  EventSystem::Trigger(new MouseScrollEvent(static_cast<float>(GET_X_LPARAM(lp)), static_cast<float>(GET_Y_LPARAM(lp)))); break;
		case WM_MOUSEMOVE:   EventSystem::Trigger(new MouseMoveEvent(static_cast<float>(GET_X_LPARAM(lp)), static_cast<float>(GET_Y_LPARAM(lp)))); break;
		}
		return DefWindowProc(window, msg, wp, lp);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		std::wstring titleWstr = std::wstring(properties.title.begin(), properties.title.end());
		const wchar_t* className = titleWstr.c_str();

		WNDCLASSEX wndclass = { sizeof(WNDCLASSEX), CS_DBLCLKS, WndProc, 0, 0, GetModuleHandle(0),
			LoadIcon(0, IDI_APPLICATION), LoadCursor(0, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), 0,
			className, LoadIcon(0, IDI_APPLICATION) };

		if (!RegisterClassEx(&wndclass)) return;

		window = CreateWindowEx(0, className, className, WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, GetModuleHandle(0), 0);

		if (!window) return;

		ShowWindow(window, SW_SHOWDEFAULT);

		PIXELFORMATDESCRIPTOR pfd =
		{
			sizeof(PIXELFORMATDESCRIPTOR),
			1,
			PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
			PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
			32,                   // Colordepth of the framebuffer.
			0, 0, 0, 0, 0, 0,
			0,
			0,
			0,
			0, 0, 0, 0,
			24,                   // Number of bits for the depthbuffer
			8,                    // Number of bits for the stencilbuffer
			0,                    // Number of Aux buffers in the framebuffer.
			PFD_MAIN_PLANE,
			0,
			0, 0, 0
		};
		hdc = GetDC(window);
		ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, 0, &pfd);
		ctx = wglCreateContext(hdc);
		wglMakeCurrent(hdc, ctx);
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
