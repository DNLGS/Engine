#ifndef WINDOW_INTERNAL_H
#define WINDOW_INTERNAL_H

#include <windows.h>

typedef enum {
    RIGHT,
    LEFT,
    MIDDLE
} Button;

typedef struct {
    int (CALLBACK *WindowCreateCallback)(HWND, CREATESTRUCT*);
    int (CALLBACK *WindowDestroyCallback)(HWND);
    int (CALLBACK *WindowCloseCallback)(HWND);
    int (CALLBACK *WindowSizeCallback)(HWND, UINT, WPARAM, LPARAM);
    int (CALLBACK *WindowActivateCallback)(HWND, WPARAM, LPARAM);
    int (CALLBACK *WindowSetFocusCallback)(HWND);
    int (CALLBACK *WindowKillFocusCallback)(HWND);

    // Input Teclado
    int (CALLBACK *WindowKeyDownCallback)(HWND, WPARAM, LPARAM);
    int (CALLBACK *WindowKeyUpCallback)(HWND, WPARAM, LPARAM);

    // Input Mouse
    int (CALLBACK *WindowMouseMoveCallback)(HWND, int, int, WPARAM);
    int (CALLBACK *WindowMouseWheelCallback)(HWND, int, int, int, WPARAM);
    int (CALLBACK *WindowMouseDown)(HWND, Button, int, int, WPARAM);
    int (CALLBACK *WindowMouseUp)(HWND, Button, int, int,WPARAM);

    // Sistema
    int (CALLBACK *WindowTimerCallback)(HWND, UINT_PTR);
    int (CALLBACK *WindowPaintCallback)(HWND, HDC, RECT);
    int (CALLBACK *WindowEraseBackGroundCallback)(HWND, WPARAM);

} WindowCallbacks;

typedef struct {
    BOOL isMainWindow;
    WindowCallbacks* callbacks;
} WindowState;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static inline WindowState* GetAppState(HWND hwnd)
{
    return (WindowState*)(GetWindowLongPtr(hwnd, GWLP_USERDATA));
}

#endif