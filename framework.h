#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Include the basic windows header files and the Direct3D header file
#include <windows.h>
#include <windowsx.h>

// OpenCV
#include <opencv2/opencv.hpp>
using namespace cv;

#include <aspose_ocr.h>

#include <TlHelp32.h>
#include <Psapi.h>

#include <d3d9.h>
#include <d3dx9.h>

// Include the Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
