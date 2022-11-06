#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

// Basic windows header files
#include <windows.h>
#include <windowsx.h>

#include <TlHelp32.h>
#include <Psapi.h>

// OpenCV
#include <opencv2/opencv.hpp>

// OCR - character recognition
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#pragma comment (lib, "ws2_32.lib")

// DirectX
#include <d3d9.h>
#include <d3dx9.h>

// Direct3D Library file
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
