#include "render/render_opengl.h"
#include "window/window_user.h"
#include "window/opengl_context.h"

CALLBACK LRESULT OnSizeCB(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
    (void)hwnd;
    (void)msg;
    (void)wparam;
    setViewPort(0,0,LOWORD(lparam),HIWORD(lparam));
    return 0;
}

int main()
{
    WindowCallbacks cb = {.WindowSizeCallback = OnSizeCB};
    WindowConfig config = {
        .mainWindow = TRUE,
        .title      = "Programa",
        .className  = "MinhaJanela",
        .x          = CW_USEDEFAULT,
        .y          = CW_USEDEFAULT,
        .width      = 800,
        .height     = 600,
        .style      = WS_OVERLAPPEDWINDOW,
        .exStyle    = 0,
        .icon       = LoadIcon(NULL, IDI_APPLICATION),
        .cursor     = LoadCursor(NULL, IDC_ARROW),
        .background = (HBRUSH)(COLOR_WINDOW + 1),
        .parent     = NULL,
        .callbacks  = &cb,
    };

    HWND hwnd = NewWindow(&config);
    
    if (!hwnd) return 1; 
    
    HGLRC context = InitOpenGL(hwnd);

    if (!gladLoadGL()) {
        return 1;
    }

    setViewPort(0,0,config.width, config.height);
    
    HDC hdc = GetDC(hwnd);
    Show(hwnd, 1);
    while (!isShouldClose())
    {
        Render();        
        SwapBuffers(hdc);
    }
    
    DeleteDC(hdc);
    wglDeleteContext(context);
    return 0;
}
