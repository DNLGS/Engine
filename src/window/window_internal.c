#include "window_internal.h"

LRESULT CALLBACK WindowCallback(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
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
        if (cb && cb->OnCreate)
            return cb->OnCreate(hwnd, (CREATESTRUCT *)lParam);
        break;

    case WM_DESTROY:
        if (cb && cb->OnDestroy)
            cb->OnDestroy(hwnd);
        if (pstate->isMainWindow)
            PostQuitMessage(0);
        return 0;

    case WM_CLOSE:
        if (cb && cb->OnClose) {
            if (cb->OnClose(hwnd))
                DestroyWindow(hwnd);
        } else {
            DestroyWindow(hwnd);
        }
        break;

    case WM_SIZE:
        if (cb && cb->OnSize)
            return cb->OnSize(hwnd, uMsg, wParam, lParam);
        break;

    case WM_ACTIVATE:
        if (cb && cb->OnActivate)
            return cb->OnActivate(hwnd, wParam, lParam);
        break;

    case WM_SETFOCUS:
        if (cb && cb->OnSetFocus)
            cb->OnSetFocus(hwnd);
        break;

    case WM_KILLFOCUS:
        if (cb && cb->OnKillFocus)
            cb->OnKillFocus(hwnd);
        break;

    case WM_KEYDOWN:
        if (cb && cb->OnKeyDown)
            return cb->OnKeyDown(hwnd, wParam, lParam);
        break;

    case WM_KEYUP:
        if (cb && cb->OnKeyUp)
            return cb->OnKeyUp(hwnd, wParam, lParam);
        break;

    case WM_MOUSEMOVE:
        if (cb && cb->OnMouseMove)
            return cb->OnMouseMove(hwnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        break;

    case WM_LBUTTONDOWN:
        if (cb && cb->OnLMouseButtonDown)
            return cb->OnLMouseButtonDown(hwnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        break;

    case WM_LBUTTONUP:
        if (cb && cb->OnLMouseButtonUp)
            return cb->OnLMouseButtonUp(hwnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        break;

    case WM_RBUTTONDOWN:
        if (cb && cb->OnRMouseButtonDown)
            return cb->OnRMouseButtonDown(hwnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        break;

    case WM_RBUTTONUP:
        if (cb && cb->OnRMouseButtonUp)
            return cb->OnRMouseButtonUp(hwnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        break;

    case WM_MBUTTONDOWN:
        if (cb && cb->OnMMouseButtonDown)
            return cb->OnMMouseButtonDown(hwnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        break;

    case WM_MBUTTONUP:
        if (cb && cb->OnMMouseButtonUp)
            return cb->OnMMouseButtonUp(hwnd, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        break;

    case WM_MOUSEWHEEL:
        if (cb && cb->OnMouseWheel)
            return cb->OnMouseWheel(hwnd, GET_WHEEL_DELTA_WPARAM(wParam), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), wParam);
        break;

    case WM_TIMER:
        if (cb && cb->OnTimer)
            return cb->OnTimer(hwnd, (UINT_PTR)wParam);
        break;

    case WM_PAINT:
        if (cb && cb->OnPaint)
            return cb->OnPaint(hwnd);
        break;

    case WM_ERASEBKGND:
        if (cb && cb->OnEraseBackground)
            return cb->OnEraseBackground(hwnd, wParam);

        
        break;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

inline WindowState* GetAppState(HWND hwnd)
{
    LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
    WindowState *pState = (WindowState*)(ptr);
    return pState;
}