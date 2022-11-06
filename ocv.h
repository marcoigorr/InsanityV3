#pragma once

class OpnCV {
public:
	BITMAPINFOHEADER bi;
	cv::Mat src;

	BITMAPINFOHEADER createBitmapHeader(int width, int height);
	cv::Mat captureScreenMat(HWND hwnd);
};

extern OpnCV* ocv;