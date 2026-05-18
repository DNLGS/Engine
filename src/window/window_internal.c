#include "window_internal.h"
#include <windowsx.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    WindowState* pstate = GetAppState(hwnd);
    WindowCallbacks* cb = (pstate) ? pstate->callbacks : NULL;
    
    switch (uMsg)
    {
    case WM_NCCREATE: {
        CREATESTRUCT* pcr = (CREATESTRUCT*)lParam;
        pstate = (WindowState*)(pcr->lpCreateParams);
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pstate);
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    case WM_CREATE:
        if (cb && cb->WindowCreateCallback)
            return cb->WindowCreateCallback(hwnd, (CREATESTRUCT *)lParam);
        break;

    case WM_DESTROY:
        if (cb && cb->WindowDestroyCallback)
            cb->WindowDestroyCallback(hwnd);
        if (pstate->isMainWindow)
            PostQuitMessage(0);
        free(pstate);
        return 0;

    case WM_CLOSE:
        if (cb && cb->WindowCloseCallback) {
            if (cb->WindowCloseCallback(hwnd))
                DestroyWindow(hwnd);
        } else {            
            DestroyWindow(hwnd);
        }
        break;

    case WM_SIZE:
        if (cb && cb->WindowSizeCallback)
            return cb->WindowSizeCallback(hwnd, uMsg, wParam, lParam);
        break;

    case WM_ACTIVATE:
        if (cb && cb->WindowActivateCallback)
            return cb->WindowActivateCallback(hwnd, wParam, lParam);
        break;

    case WM_SETFOCUS:
        if (cb && cb->WindowSetFocusCallback)
            cb->WindowSetFocusCallback(hwnd);
        break;

    case WM_KILLFOCUS:
        if (cb && cb->WindowKillFocusCallback)
            cb->WindowKillFocusCallback(hwnd);
        break;

    case WM_KEYDOWN:
        if (cb && cb->WindowKeyDownCallback)
            return cb->WindowKeyDownCallback(hwnd, wParam, lParam);
        break;

    case WM_KEYUP:
        if (cb && cb->WindowKeyUpCallback)
            return cb->WindowKeyUpCallback(hwnd, wParam, lParam);
        break;

    case WM_MOUSEMOVE:
        if (cb && cb->WindowMouseMoveCallback)
            return cb->WindowMouseMoveCallback(hwnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        break;
    
    case WM_LBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MBUTTONUP:
    { 
        int btn;
        switch (uMsg)
        {
            case WM_LBUTTONUP:
                btn = LEFT; 
                break;
            case WM_RBUTTONUP:
                btn = RIGHT;
                break;
            case WM_MBUTTONUP:
                btn = MIDDLE;
                break;        
        }
        
        if (cb && cb->WindowMouseUp)
        {            
            return cb->WindowMouseUp(hwnd, (Button)btn, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        }
        break;
    } 

    case WM_LBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_MBUTTONDOWN:
    {
        int btn;
        switch (uMsg)
        {
            case WM_LBUTTONDOWN:
                btn = LEFT;
                break;
            case WM_RBUTTONDOWN:
                btn = RIGHT;
                break;
            case WM_MBUTTONDOWN:
                btn = MIDDLE;
                break;        
        }
        
        if (cb && cb->WindowMouseDown)
        {            
            return cb->WindowMouseDown(hwnd, (Button)btn, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        }
        break;
    } 
    
    case WM_MOUSEWHEEL:
        if (cb && cb->WindowMouseWheelCallback)
            return cb->WindowMouseWheelCallback(hwnd, GET_WHEEL_DELTA_WPARAM(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        break;

    case WM_TIMER:
        if (cb && cb->WindowTimerCallback)
            return cb->WindowTimerCallback(hwnd, (UINT_PTR)wParam);
        break;

    case WM_PAINT:{
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd,&ps);
        if (cb && cb->WindowPaintCallback)
            return cb->WindowPaintCallback(hwnd,hdc,ps.rcPaint);
        EndPaint(hwnd,&ps);
        break;
    }    
    case WM_ERASEBKGND:
        if (cb && cb->WindowEraseBackGroundCallback)
            return cb->WindowEraseBackGroundCallback(hwnd, wParam);
        
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}