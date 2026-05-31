#include "render/render_opengl.h"
#include "window/window_user.h"
#include "window/opengl_context.h"
#include "render/render_opengl.h"

CALLBACK LRESULT OnSizeCB(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam){
    (void)hwnd;
    (void)msg;
    (void)wparam;
    setViewPort(0,0,LOWORD(lparam),HIWORD(lparam));
    return 0;
}

typedef struct{
    uint shaderProgram;
    uint vao;
} DataDraw;


WindowCallbacks cb = {.WindowSizeCallback = OnSizeCB};    

void render_func(void* data){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    DataDraw* draw = (DataDraw*)data;
    
    glUseProgram(draw->shaderProgram);
    glBindVertexArray(draw->vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main()
{
    WindowConfig mainWindowConfig = {
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

    HWND hwnd = NewWindow(&mainWindowConfig);
    if (!hwnd) return 1; 
    
    HGLRC context = InitOpenGL(hwnd);

    if (!gladLoadGL()) {
        return 1;
    }

    setViewPort(0,0,mainWindowConfig.width, mainWindowConfig.height);

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };  

    uint lvao = vao();
    uint lvbo = vbo(vertices, sizeof(vertices),DYNAMIC);
    uint lvert = compile_shader("E:\\Sistemas\\C\\Engine\\lib\\shaders\\vertex.vert", VERTEX);
    uint lfrag = compile_shader("E:\\Sistemas\\C\\Engine\\lib\\shaders\\frag.frag", FRAGMENT);
    uint lprog = shader_program();
    uint lshaders[2] = {lvert,lfrag};
    
    attach_shader_program(lprog,lshaders,2);

    DataDraw draw = {
        .shaderProgram = lprog,
        .vao =  lvao
    };
    
    HDC hdc = GetDC(hwnd);
    Show(hwnd, 1);    
    while (!isShouldClose())
    {
        Render(render_func,&draw);        
        SwapBuffers(hdc);
    }
    
    DeleteDC(hdc);
    wglDeleteContext(context);
    return 0;
}
