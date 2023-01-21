#include "Precompiled.h"
#include "WindowMessageHandler.h"

void NEng::WindowMessageHandler::Hook(HWND window, Callback cb)
{
	mWindow = window;
	mPreviousCallback = (Callback)GetWindowLongPtrA(window, GWLP_WNDPROC);
	SetWindowLongPtrA(window, GWLP_WNDPROC, (LONG_PTR)cb);
}

void NEng::WindowMessageHandler::Unhook()
{
	SetWindowLongPtrA(mWindow, GWLP_WNDPROC, (LONG_PTR)mPreviousCallback);
	mWindow = nullptr;
}

LRESULT NEng::WindowMessageHandler::FowardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	return CallWindowProcA((WNDPROC)mPreviousCallback, window, message, wParam, lParam);
}
