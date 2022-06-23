#include "WindowsWindow.hpp"
#include <iostream>
#include <Junia/Events/WindowEvents.hpp>

namespace Junia
{
	/*Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
	}*/

	LRESULT CALLBACK WndProc(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
	{
		switch (msg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0L;
		case WM_LBUTTONDOWN:
			std::cout << "\nmouse left button down at (" << LOWORD(lp) << ',' << HIWORD(lp) << ")\n";
			[[fallthrough]];
		default:
			return DefWindowProc(window, msg, wp, lp);
		}
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
	}

	WindowsWindow::~WindowsWindow()
	{
		Close();
	}

	void WindowsWindow::OnUpdate()
	{
		MSG msg;
		if (GetMessage(&msg, window, 0, 0))
		{
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

	}
}
