#ifndef WINDOW_USER_H
#define WINDOW_USER_H
#include "window_internal.h"

typedef struct {
    BOOL               mainWindow;
    const char        *title;
    const char        *className;
    int                x, y;
    int                width, height;
    DWORD              style;
    DWORD              exStyle;
    HICON              icon;
    HCURSOR            cursor;
    HBRUSH             background;
    HWND               parent;
    WindowCallbacks    *callbacks;
} WindowConfig;

HWND NewWindow(WindowConfig*);
BOOL Show(HWND, int);
BOOL isShouldClose();

#endif