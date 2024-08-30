#include <windows.h>

const char g_szClassName[] = "myWindowCLass";

// Step 4: The Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_LBUTTONDOWN:
        {
            char szFileName[MAX_PATH];
            HINSTANCE hInstance = GetModuleHandle(NULL);

            GetModuleFileName(hInstance, szFileName, MAX_PATH);

            MessageBox(hwnd, szFileName, "This program is:", MB_ICONINFORMATION | MB_OK);
        }
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    // Step 1: Registering the window class
    wc.cbClsExtra           = 0;
    wc.cbSize               = sizeof(WNDCLASSEX);
    wc.cbWndExtra           = 0;
    wc.hbrBackground        = (HBRUSH) (COLOR_WINDOW + 1);
    wc.hCursor              = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon                = LoadIcon(NULL, IDI_SHIELD);
    wc.hIconSm              = LoadIcon(NULL, IDI_SHIELD);
    wc.hInstance            = hInstance;
    wc.lpfnWndProc          = WndProc;
    wc.lpszClassName        = g_szClassName;
    wc.lpszMenuName         = NULL;
    wc.style                = 0;

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);

        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "My Window",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        400, 200,
        NULL, NULL,
        hInstance,
        NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);

        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
    
}