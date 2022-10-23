#pragma once

class wnd
{
public:
	HWND hwndDesktop;
	HWND hWnd; // Handle for the window

	// if GetDesktopResolution fails then uses these default values
	int SCREEN_WIDTH = 1920; 
	int SCREEN_HEIGHT = 1080;

	void CreateWnd(HINSTANCE hInstance);
	void GetDesktopResolution(int& horizontal, int& vertical);

	wnd()
	{
		hwndDesktop = GetDesktopWindow();
		GetDesktopResolution(SCREEN_WIDTH, SCREEN_HEIGHT);
	}
};

extern wnd* window;


