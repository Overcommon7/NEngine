#include "Precompiled.h"
#include "Window.h"

LRESULT CALLBACK WindowMessageHandler(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_QUIT:
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(handle, message, wParam, lParam);
}

void Window::Initialize(HINSTANCE Instance, const wstring& appname, uint32_t width, uint32_t height)
{
	instance = Instance;
	appName = std::move(appname);
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WindowMessageHandler;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = instance;
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = appName.c_str();
	wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	RegisterClassEx(&wc);

	RECT rc{ 0, 0, (LONG)width, (LONG)height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	const int screenwidth = GetSystemMetrics(SM_CXSCREEN);
	const int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	const int winWidth = std::min(static_cast<int> (rc.right - rc.left), screenwidth); 
	const int winHeight = std::min(static_cast<int>(rc.bottom - rc.top), screenHeight);
	const int left = (screenwidth - winWidth) / 2;
	const int top = (screenHeight - winHeight) / 2;
	wnd = CreateWindow(appName.c_str(),
		appName.c_str(),
		WS_OVERLAPPEDWINDOW,
		left, top,
		winWidth, winHeight,
		nullptr, nullptr,
		instance, nullptr);

	ShowWindow(wnd, SW_SHOWNORMAL);

	isActive = (wnd != nullptr);
}

void Window::Terminate()
{
	DestroyWindow(wnd);
	UnregisterClassW(appName.c_str(), instance);
	wnd = nullptr;
	instance = nullptr;
}

void Window::ProcessMessage()
{
	MSG msg;

	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			isActive = false;
			return;
		}
			

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
