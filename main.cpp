#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <windowsx.h>
#include <dwmapi.h>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // Register the window class.
    const wchar_t CLASS_NAME[] = L"Sample Window Class";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwnd = CreateWindowEx(
        0, // Optional window styles.
        CLASS_NAME, // Window class
        L"Learn to Program Windows", // Window text
        WS_OVERLAPPEDWINDOW, // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL, // Parent window
        NULL, // Menu
        hInstance, // Instance handle
        NULL // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }

    // SetWindowLong(hwnd,GWL_STYLE,WS_THICKFRAME & ~WS_CAPTION);
    // SetWindowPos(hwnd,nullptr,0,0,0,0,SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
    ShowWindow(hwnd, nCmdShow);

    MARGINS margins = {1};
    DwmExtendFrameIntoClientArea(hwnd, &margins);
    // Run the message loop.

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

const int TopHeight = 6;
const int LeftWidth = 6;
const int BottomHeight = 6;
const int RightWidth = 6;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_NCCALCSIZE:
            return 0;
        case WM_NCHITTEST: {
            POINT ptMouse = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};

            // Get the window rectangle.
            RECT rcWindow;
            GetWindowRect(hWnd, &rcWindow);

            // Get the frame rectangle, adjusted for the style without a caption.
            RECT rcFrame = {0};
            AdjustWindowRectEx(&rcFrame, WS_OVERLAPPEDWINDOW & ~WS_CAPTION, FALSE, NULL);

            // Determine if the hit test is for resizing. Default middle (1,1).
            USHORT uRow = 1;
            USHORT uCol = 1;
            bool fOnResizeBorder = false;

            // Determine if the point is at the top or bottom of the window.
            if (ptMouse.y >= rcWindow.top && ptMouse.y < rcWindow.top + TopHeight) {
                fOnResizeBorder = (ptMouse.y < (rcWindow.top - rcFrame.top));
                uRow = 0;
            } else if (ptMouse.y < rcWindow.bottom && ptMouse.y >= rcWindow.bottom - BottomHeight) {
                uRow = 2;
            }

            // Determine if the point is at the left or right of the window.
            if (ptMouse.x >= rcWindow.left && ptMouse.x < rcWindow.left + LeftWidth) {
                uCol = 0; // left side
            } else if (ptMouse.x < rcWindow.right && ptMouse.x >= rcWindow.right - RightWidth) {
                uCol = 2; // right side
            }

            // Hit test (HTTOPLEFT, ... HTBOTTOMRIGHT)
            LRESULT hitTests[3][3] =
            {
                {HTTOPLEFT, fOnResizeBorder ? HTTOP : HTCAPTION, HTTOPRIGHT},
                {HTLEFT, HTNOWHERE, HTRIGHT},
                {HTBOTTOMLEFT, HTBOTTOM, HTBOTTOMRIGHT},
            };

            return hitTests[uRow][uCol];
        }
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // All painting occurs here, between BeginPaint and EndPaint.

            auto brush = CreateSolidBrush(RGB(255, 0, 0));
            FillRect(hdc, &ps.rcPaint, brush);

            EndPaint(hWnd, &ps);
            return 0;
        }
    }
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
