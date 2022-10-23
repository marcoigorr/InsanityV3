#include "framework.h"
#include "ocv.h"

#include "wnd.h"

BITMAPINFOHEADER OpnCV::createBitmapHeader(int width, int height)
{
	// Create bitmap
	bi.biSize = sizeof(bi);
	bi.biWidth = width;
	bi.biHeight = -height;
	bi.biPlanes = 1;
	bi.biBitCount = 32;
	bi.biCompression = BI_RGB;
	bi.biSizeImage = 0;
	bi.biXPelsPerMeter = 0;
	bi.biYPelsPerMeter = 0;
	bi.biClrUsed = 0;
	bi.biClrImportant = 0;

	return bi;
}

Mat OpnCV::captureScreenMat(HWND hwnd)
{
	Mat src;

	// Get handle to a device context (DC)
	HDC hwindowDC = GetDC(hwnd);
	HDC hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);

	// Define scale, height and width
	int screenx = GetSystemMetrics(SM_XVIRTUALSCREEN);
	int screeny = GetSystemMetrics(SM_YVIRTUALSCREEN);
	int width = window->SCREEN_WIDTH;
	int height = window->SCREEN_HEIGHT;

	// Create mat object
	src.create(height, width, CV_8UC4);

	// Create Bitmap
	HBITMAP hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
	BITMAPINFOHEADER bi = ocv->createBitmapHeader(width, height);

	// Use DC with the bitmap
	SelectObject(hwindowCompatibleDC, hbwindow);

	// Copy from the window DC to the bitmap DC
	StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, screenx, screeny, width, height, SRCCOPY);
	GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

	// Avoid memory leak
	DeleteObject(hbwindow);
	DeleteDC(hwindowCompatibleDC);
	ReleaseDC(hwnd, hwindowCompatibleDC);

	return src;
}

OpnCV* ocv = new OpnCV();