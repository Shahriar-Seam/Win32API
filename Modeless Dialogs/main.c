#include "resource.h"

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("Modeless Dialogs");
HWND g_hToolbar = NULL;

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = MAKEINTRESOURCE(IDR_MYMENU);
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Modeless Dialogs"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0) > 0)
    {
        if (!IsDialogMessage(g_hToolbar, &messages)) {
            /* Translate virtual-key messages into character messages */
            TranslateMessage(&messages);
            /* Send message to WindowProcedure */
            DispatchMessage(&messages);
        }
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            g_hToolbar = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TOOLBAR), hwnd, ToolDlgProc);

            if (g_hToolbar != NULL) {
                ShowWindow(g_hToolbar, SW_SHOW);
            }
            else {
                MessageBox(hwnd, "CreateDialog returned NULL", "Warning!", MB_OK | MB_ICONINFORMATION);
            }

            break;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case ID_DIALOG_SHOW:
                    ShowWindow(g_hToolbar, SW_SHOW);
                    break;
                case ID_DIALOG_HIDE:
                    ShowWindow(g_hToolbar, SW_HIDE);
                    break;
                case ID_FILE_EXIT:
                    DestroyWindow(hwnd);
                    PostQuitMessage(0);
                    break;
            }
            break;
        case WM_DESTROY:
            DestroyWindow(g_hToolbar);
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;

        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
    switch (Message)
    {
        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDC_PRESS:
                    MessageBox(hwnd, "Hi!", "This is a message", MB_OK | MB_ICONEXCLAMATION);
                    break;
                case IDC_OTHER:
                    MessageBox(hwnd, "Bye!", "This is another message", MB_OK | MB_ICONEXCLAMATION);
                    break;
            }

            break;
        case WM_DESTROY:
            DestroyWindow(g_hToolbar);
            PostQuitMessage(0);
            break;

        default:
            return FALSE;
    }

    return TRUE;
}
