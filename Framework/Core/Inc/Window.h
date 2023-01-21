#pragma once

class Window
{
public:
	void Initialize(HINSTANCE instance, const wstring& appname, uint32_t width, uint32_t hieght);
	void Terminate();
	void PrrocessMessage();

	HWND wnd;
	wstring appName;
	HINSTANCE instance;
	bool isActive;
};
