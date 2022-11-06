#include "framework.h"

#include "wnd.h"
#include "d3d.h"
#include "ocv.h"

#include "option.h"


LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    } break;
    }

    return DefWindowProc(hWnd, message, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
    // Fullscreen transparent window creation
    window->CreateWnd(hInstance);

    // Display created window
    ShowWindow(window->hWnd, nCmdShow);

    // Set up and initialize Direct3D and ImGui
    d3d9->initD3D(window->hWnd);

    // Initialize tesseract-ocr with English, without specifying tessdata path
    tesseract::TessBaseAPI* ocr = new tesseract::TessBaseAPI();
    
    // Initialize tesseract (eng) and the LSTM OCR engine (deep learning)
    if (ocr->Init("C:\\src\\TesseractData\\tessdata\\", "eng"))
        exit(1);

    ocr->SetPageSegMode(tesseract::PSM_AUTO);

    MSG msg;

    // Main loop
    while (!(GetAsyncKeyState(VK_F9)))
    {
        // Check to see if any messages are waiting in the queue
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        if (msg.message == WM_QUIT)
            break;

        // Insert for hide/unhide text
        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            option->bVisible = !option->bVisible;
        }  

        if (GetAsyncKeyState(VK_HOME) & 1)
        {
            option->bIconVisible = !option->bIconVisible;

            if (option->bIconVisible)
            {
                ShowWindow(window->hWnd, SW_HIDE);
            }
            else {
                ShowWindow(window->hWnd, nCmdShow);
            }
        }

        if (GetAsyncKeyState(VK_F1) & 1)
        {      
            // Get Screenshot  
            ocv->src = ocv->captureScreenMat(window->hwndDesktop);
            cv::imwrite("Screenshot.png", ocv->src);
            cv::Mat im = cv::imread("Screenshot.png", cv::IMREAD_COLOR);

            ocr->SetImage(im.data, im.cols, im.rows, 3, im.step);
            option->text = ocr->GetUTF8Text();
        }

        // Render frame and ImGui 
        d3d9->renderFrame();
    }

    // Clean DirectX and COM
    d3d9->cleanD3D();

    // Destroy tess obj 
    ocr->End();

    // Return this part of the WM_QUIT message to Windows
    return msg.wParam;
}