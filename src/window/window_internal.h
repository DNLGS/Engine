#ifndef WINDOW_INTERNAL_H
#define WINDOW_INTERNAL_H

#include <windows.h>

typedef enum {
    RIGHT,
    LEFT,
    MIDDLE
} Button;

typedef struct {
    LRESULT (CALLBACK *WindowCreateCallback)(HWND, CREATESTRUCT*);
    LRESULT (CALLBACK *WindowDestroyCallback)(HWND);
    LRESULT (CALLBACK *WindowCloseCallback)(HWND);
    LRESULT (CALLBACK *WindowSizeCallback)(HWND, UINT, WPARAM, LPARAM);
    LRESULT (CALLBACK *WindowActivateCallback)(HWND, WPARAM, LPARAM);
    LRESULT (CALLBACK *WindowSetFocusCallback)(HWND);
    LRESULT (CALLBACK *WindowKillFocusCallback)(HWND);

    // Input Teclado
    LRESULT (CALLBACK *WindowKeyDownCallback)(HWND, WPARAM, LPARAM);
    LRESULT (CALLBACK *WindowKeyUpCallback)(HWND, WPARAM, LPARAM);

    // Input Mouse
    LRESULT (CALLBACK *WindowMouseMoveCallback)(HWND, int, int, WPARAM);
    LRESULT (CALLBACK *WindowMouseWheelCallback)(HWND, int, int, int, WPARAM);
    LRESULT (CALLBACK *WindowMouseDown)(HWND, Button, int, int, WPARAM);
    LRESULT (CALLBACK *WindowMouseUp)(HWND, Button, int, int,WPARAM);

    // Sistema
    LRESULT (CALLBACK *WindowTimerCallback)(HWND, UINT_PTR);
    LRESULT (CALLBACK *WindowPaintCallback)(HWND, HDC, RECT);
    LRESULT (CALLBACK *WindowEraseBackGroundCallback)(HWND, WPARAM);

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