#include "Win32.hpp"

#if JE_WINDOWAPI == JE_WINDOWAPI_WIN32

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <timeapi.h>
#include <windowsx.h>

unsigned long WinTime_GetTime() { return timeGetTime(); }

int Win32_Get_X_LPARAM(const long long lp) { return GET_X_LPARAM(lp); }
int Win32_Get_Y_LPARAM(const long long lp) { return GET_Y_LPARAM(lp); }

long long Win32_DefWindowProc(Win32_HWND hWnd, unsigned int Msg, unsigned long long wParam, long long lParam) { return DefWindowProc(hWnd, Msg, wParam, lParam); }
int Win32_SetProcessDpiAwarenessContext(Win32_DPI_AWARENESS_CONTEXT value) { return SetProcessDpiAwarenessContext(value); }
int Win32_ShowWindow(Win32_HWND hWnd, int nCmdShow) { return ShowWindow(hWnd, nCmdShow); }
LPRECT Win32RectPtrToRectPtr(Win32_LPRECT rect) { return reinterpret_cast<RECT*>(rect); }
int Win32_GetWindowRect(Win32_HWND hWnd, Win32_LPRECT rect) { return GetWindowRect(hWnd, Win32RectPtrToRectPtr(rect)); }
unsigned int Win32_GetDpiForSystem() { return GetDpiForSystem(); }
unsigned int Win32_GetDpiForWindow(Win32_HWND hWnd) { return GetDpiForWindow(hWnd); }
short Win32_Get_Wheel_Delta_WPARAM(unsigned long long wp) { return GET_WHEEL_DELTA_WPARAM(wp); }
Win32_HMODULE Win32_GetModuleHandle(Win32_LPCWSTR lpModuleName) { return GetModuleHandle(lpModuleName); }
Win32_HICON Win32_LoadIcon(Win32_HINSTANCE hInstance, Win32_LPCWSTR lpIconName) { return LoadIcon(hInstance, lpIconName); }
Win32_HCURSOR Win32_LoadCursor(Win32_HINSTANCE hInstance, Win32_LPCWSTR lpCursorName) { return LoadCursor(hInstance, lpCursorName); }
unsigned short Win32_RegisterClassEx(const Win32_WNDCLASSEX* wndclass) { return RegisterClassEx(reinterpret_cast<const WNDCLASSEX*>(wndclass)); }
Win32_HWND Win32_CreateWindowEx(unsigned long dwExStyle, Win32_LPCWSTR lpClassName, Win32_LPCWSTR lpWindowName, unsigned long dwStyle, int X, int Y, int nWidth, int nHeight, Win32_HWND hWndParent, Win32_HMENU hMenu, Win32_HINSTANCE hInstance, void* lpParam)
{
	return CreateWindowEx(
		dwExStyle,
		lpClassName,
		lpWindowName,
		dwStyle,
		X, Y,
		nWidth, nHeight,
		hWndParent,
		hMenu,
		hInstance,
		lpParam
	);
}
Win32_HDC Win32_GetDC(Win32_HWND hWnd) { return GetDC(hWnd); }
int Win32_ChoosePixelFormat(Win32_HDC hdc, const Win32_PIXELFORMATDESCRIPTOR* ppfd) { return ChoosePixelFormat(hdc, reinterpret_cast<const PIXELFORMATDESCRIPTOR*>(ppfd)); }
unsigned long Win32_GetLastError() { return GetLastError(); }
int Win32_SetPixelFormat(Win32_HDC hdc, int format, const Win32_PIXELFORMATDESCRIPTOR* ppfd) { return SetPixelFormat(hdc, format, reinterpret_cast<const PIXELFORMATDESCRIPTOR*>(ppfd)); }
int Win32_MoveWindow(Win32_HWND hWnd, int X, int Y, int nWidth, int nHeight, int bRepaint) { return MoveWindow(hWnd, X, Y, nWidth, nHeight, bRepaint); }
int Win32_TranslateMessage(const Win32_MSG* lpMsg) { return TranslateMessage(reinterpret_cast<const MSG*>(lpMsg)); }
long long Win32_DispatchMessage(const Win32_MSG* lpMsg) { return DispatchMessage(reinterpret_cast<const MSG*>(lpMsg)); }
int Win32_PeekMessage(Win32_LPMSG lpMsg, Win32_HWND hWnd, unsigned int wMsgFilterMin, unsigned int wMsgFilterMax, unsigned int wRemoveMsg) { return PeekMessage(reinterpret_cast<LPMSG>(lpMsg), hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg); }
int Win32_SwapBuffers(Win32_HDC hdc) { return SwapBuffers(hdc); }

Win32_HGLRC WGL_CreateContext(Win32_HDC hdc) { return wglCreateContext(hdc); }
int WGL_DeleteContext(Win32_HGLRC hglrc) { return wglDeleteContext(hglrc); }
int WGL_MakeCurrent(Win32_HDC hdc, Win32_HGLRC hglrc) { return wglMakeCurrent(hdc, hglrc); }

short Win32_GetKeyState(int nVirtKey) { return GetKeyState(nVirtKey); }
int Win32_GetCursorPos(Win32_LPPOINT lpPoint) { return GetCursorPos(reinterpret_cast<LPPOINT>(lpPoint)); }

#endif
