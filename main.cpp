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

    MSG msg;

    // OCR info
    std::string image_path = "Screenshot.png";

    const size_t len = 4096;

    // Main loop
    while (!(GetAsyncKeyState(VK_HOME)))
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
        if (GetAsyncKeyState(VK_F3) & 1)
        {
            option->bVisible = !option->bVisible;
        }  

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {      
            wchar_t output[len] = { 0 };

            // Get Screenshot  
            ocv->src = ocv->captureScreenMat(window->hwndDesktop);
            imwrite("Screenshot.png", ocv->src);

            int cont = 0;

            int x = 100, y = 50, w = 1920, h = 200;
            for (uint i = y; i <= 1050; i += 200)
            {
                wchar_t buffer[len] = { 0 };

                // Get text from image
                size_t size = aspose::ocr::page_rect_abc(image_path.c_str(), buffer, len, x, y, w, i, 
                    L" !\",#$%&()*+,-./0123456789:;<=>?@[\\]_`{|}"
                    "~ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");

                for (int j = 0; j < len; j++)
                {
                    output[cont] += buffer[j];
                    cont++;
                }
            }            
        }

        // Render frame and ImGui
        d3d9->renderFrame();
    }

    // Clean DirectX and COM
    d3d9->cleanD3D();

    // Return this part of the WM_QUIT message to Windows
    return msg.wParam;
}