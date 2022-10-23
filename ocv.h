#pragma once

class OpnCV {
public:
	BITMAPINFOHEADER bi;
	Mat src;

	BITMAPINFOHEADER createBitmapHeader(int width, int height);
	Mat captureScreenMat(HWND hwnd);
};

extern OpnCV* ocv;