#include <glad/glad.h>
#include "window/window_user.h"
#include "render/opengl_render.h"

int OnSizeCB(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
    (void)hwnd;
    (void)msg;
    (void)wparam;
    glViewport(0,0,LOWORD(lparam),HIWORD(lparam));
    return 0;
}

int main()
{
    WindowCallbacks cb = {.OnSize= OnSizeCB};
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

    glViewport(0,0,config.width, config.height);
    
    HDC hdc = GetDC(hwnd);
    Show(hwnd, 1);
    while (!isShouldClose())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        SwapBuffers(hdc);
    }
    
    DeleteDC(hdc);
    wglDeleteContext(context);
    return 0;
}
