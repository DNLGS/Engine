#ifndef WINDOW_INTERNAL_H
#define WINDOW_INTERNAL_H

#include <windows.h>

// Sistema
extern int (*WindowCreateCallback)(HWND hwnd, CREATESTRUCT *cs);
extern int (*WindowDestroyCallback)(HWND hwnd);
extern int (*WindowCloseCallback)(HWND hwnd);
extern int (*WindowSizeCallback)(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern int (*WindowActivateCallback)(HWND hwnd, WPARAM wParam, LPARAM lParam);
extern int (*WindowSetFocusCallback)(HWND hwnd);
extern int (*WindowKillFocusCallback)(HWND hwnd);

// Input Teclado
extern int (*WindowKeyDownCallback)(HWND hwnd, WPARAM vkCode, LPARAM flags);
extern int (*WindowKeyUpCallback)(HWND hwnd, WPARAM vkCode, LPARAM flags);

// Input Mouse
extern int (*WindowMouseMoveCallback)(HWND hwnd, int x, int y, WPARAM keyFlags);
extern int (*WindowLMouseButtonDownCallback)(HWND hwnd, int button, int x, int y, WPARAM keyFlags);
extern int (*WindowLMouseButtonUpCallback)(HWND hwnd, int button, int x, int y, WPARAM keyFlags);
extern int (*WindowRMouseButtonDownCallback)(HWND hwnd, int button, int x, int y, WPARAM keyFlags);
extern int (*WindowRMouseButtonUpCallback)(HWND hwnd, int button, int x, int y, WPARAM keyFlags);
extern int (*WindowMMouseButtonDownCallback)(HWND hwnd, int button, int x, int y, WPARAM keyFlags);
extern int (*WindowMMouseButtonUpCallback)(HWND hwnd, int button, int x, int y, WPARAM keyFlags);
extern int (*WindowMouseWheelCallback)(HWND hwnd, int delta, int x, int y, WPARAM keyFlags);

// Sistema
extern int (*WindowTimerCallback)(HWND hwnd, UINT_PTR timerId);
extern int (*WindowPaintCallback)(HWND hwnd);
extern int (*WindowEraseBackGroundCallback)(HWND hwnd, WPARAM id);

typedef struct {
    int (*OnCreate)(HWND, CREATESTRUCT *);
    int (*OnDestroy)(HWND);
    int (*OnClose)(HWND);
    int (*OnSize)(HWND, UINT, WPARAM, LPARAM);
    int (*OnActivate)(HWND, WPARAM, LPARAM);
    int (*OnSetFocus)(HWND);
    int (*OnKillFocus)(HWND);
    int (*OnKeyDown)(HWND, WPARAM, LPARAM);
    int (*OnKeyUp)(HWND, WPARAM, LPARAM);
    int (*OnMouseMove)(HWND, int, int, WPARAM);
    int (*OnLMouseButtonDown)(HWND, int, int, WPARAM);
    int (*OnLMouseButtonUp)(HWND, int, int, WPARAM);
    int (*OnRMouseButtonDown)(HWND, int, int, WPARAM);
    int (*OnRMouseButtonUp)(HWND, int, int, WPARAM);
    int (*OnMMouseButtonDown)(HWND, int, int, WPARAM);
    int (*OnMMouseButtonUp)(HWND, int, int, WPARAM);
    int (*OnMouseWheel)(HWND, int, int, int, WPARAM);
    int (*OnTimer)(HWND, UINT_PTR);
    int (*OnPaint)(HWND);
    int (*OnEraseBackground)(HWND, WPARAM);
} WindowCallbacks;

typedef struct {
    BOOL isMainWindow;
    WindowCallbacks* callbacks;
} WindowState;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static inline WindowState* GetAppState(HWND hwnd)
{
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    return (WindowState*)(ptr);
}

#endif