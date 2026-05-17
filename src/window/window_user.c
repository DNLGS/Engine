#include "window_user.h"

HWND NewWindow(WindowConfig *config)
{
    WindowState *state = malloc(sizeof(WindowState));
    state->callbacks = config->callbacks;
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = config->className;
    wc.hIcon         = config->icon;
    wc.hCursor       = config->cursor;
    wc.hbrBackground = config->background;

    state->isMainWindow = config->mainWindow;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        config->exStyle,
        config->className,
        config->title,
        config->style,
        config->x, config->y,
        config->width, config->height,
        config->parent,
        NULL,
        hInstance,
        state 
    );

    if (hwnd == NULL)
    {
        free(state);
        return NULL;
    }

    return hwnd;
}

BOOL Show(HWND hwnd, int mode){
    return ShowWindow(hwnd, mode);
}

BOOL isShouldClose(){    
    MSG msg;
    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
        if (msg.message == WM_QUIT)
            return TRUE;

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return FALSE;
}
