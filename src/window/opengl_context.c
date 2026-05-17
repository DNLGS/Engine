#include "opengl_context.h"

// Creditos ao https://github.com/ColleagueRiley/OpenGL-Context-Creation

#include <stdio.h>
#include <stdint.h>
#include <assert.h>

typedef uint8_t     u8;
typedef int8_t      i8;
typedef uint16_t   u16;
typedef int16_t    i16;
typedef uint32_t   u32;
typedef int32_t    i32;
typedef uint64_t   u64;
typedef int64_t    i64;
typedef u8 b8;

#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB 0x00000001
#define WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB 0x00000002
#define WGL_CONTEXT_MAJOR_VERSION_ARB             0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB             0x2092
#define WGL_CONTEXT_PROFILE_MASK_ARB              0x9126

HGLRC InitOpenGL(HWND hwnd)
{
    // --- Tipos de função WGL ---
    typedef HGLRC (WINAPI *PFNWGLCREATECONTEXTATTRIBSARBPROC)(HDC, HGLRC, const int *);
    typedef BOOL  (WINAPI *PFNWGLCHOOSEPIXELFORMATARBPROC)(HDC, const int *, const FLOAT *, UINT, int *, UINT *);
    typedef BOOL  (WINAPI *PFNWGLSWAPINTERVALEXTPROC)(int);

    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
    PFNWGLCHOOSEPIXELFORMATARBPROC    wglChoosePixelFormatARB    = NULL;
    PFNWGLSWAPINTERVALEXTPROC         wglSwapIntervalEXT         = NULL;

    // --- Janela e contexto dummy ---
    WNDCLASS dummyWc = {0};
    dummyWc.lpfnWndProc   = DefWindowProc;
    dummyWc.hInstance     = GetModuleHandle(NULL);
    dummyWc.lpszClassName = "DummyOpenGLWindow";
    RegisterClass(&dummyWc);

    HWND dummyWin = CreateWindowA("DummyOpenGLWindow", "Dummy",
                                0, 0, 0, 0, 0,
                                NULL, NULL, dummyWc.hInstance, NULL);
    HDC dummyDC = GetDC(dummyWin);

    PIXELFORMATDESCRIPTOR pfd = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        32,    // cColorBits
        0, 0, 0, 0, 0, 0,
        8,     // cAlphaBits
        0, 0, 0, 0, 0, 0,
        24,    // cDepthBits
        8,     // cStencilBits
        0,
        PFD_MAIN_PLANE,
        0, 0, 0, 0
    };

    int pf = ChoosePixelFormat(dummyDC, &pfd);
    SetPixelFormat(dummyDC, pf, &pfd);

    HGLRC dummyCtx = wglCreateContext(dummyDC);
    wglMakeCurrent(dummyDC, dummyCtx);

    // --- Carregar extensões WGL ---
    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)
        wglGetProcAddress("wglCreateContextAttribsARB");
    wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)
        wglGetProcAddress("wglChoosePixelFormatARB");
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)
        wglGetProcAddress("wglSwapIntervalEXT");

    // --- Destruir dummy ---
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(dummyCtx);
    ReleaseDC(dummyWin, dummyDC);
    DestroyWindow(dummyWin);

    // --- Atributos de pixel para contexto moderno ---
    int attribs[] = {
        0x2003, 0x2027,   // WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB
        0x2010, 1,         // WGL_SUPPORT_OPENGL_ARB
        0x2001, 1,         // WGL_DRAW_TO_WINDOW_ARB
        0x2013, 0x202B,    // WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB
        0x2014, 32,        // WGL_COLOR_BITS_ARB
        0x2015, 8,         // WGL_RED_BITS_ARB
        0x2017, 8,         // WGL_GREEN_BITS_ARB
        0x2019, 8,         // WGL_BLUE_BITS_ARB
        0x201b, 8,         // WGL_ALPHA_BITS_ARB
        0x2022, 24,        // WGL_DEPTH_BITS_ARB
        0x2023, 8,         // WGL_STENCIL_BITS_ARB
        0x2011, 1,         // WGL_DOUBLE_BUFFER_ARB
        0, 0
    };

    HDC hdc = GetDC(hwnd);
    int pixelFormat;
    UINT numFormats;

    if (!wglChoosePixelFormatARB(hdc, attribs, NULL, 1, &pixelFormat, &numFormats) || numFormats == 0)
    {
        printf("wglChoosePixelFormatARB falhou.\n");
        ReleaseDC(hwnd, hdc);
        return NULL;
    }

    PIXELFORMATDESCRIPTOR pfdResult;
    DescribePixelFormat(hdc, pixelFormat, sizeof(pfdResult), &pfdResult);
    if (!SetPixelFormat(hdc, pixelFormat, &pfdResult))
    {
        printf("SetPixelFormat falhou.\n");
        ReleaseDC(hwnd, hdc);
        return NULL;
    }

    // --- Atributos do contexto OpenGL ---
    int contextAttribs[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
        WGL_CONTEXT_MINOR_VERSION_ARB, 6,
        WGL_CONTEXT_PROFILE_MASK_ARB,  WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    HGLRC ctx = wglCreateContextAttribsARB(hdc, NULL, contextAttribs);
    if (!ctx)
    {
        printf("wglCreateContextAttribsARB falhou.\n");
        ReleaseDC(hwnd, hdc);
        return NULL;
    }

    wglMakeCurrent(hdc, ctx);
    ReleaseDC(hwnd, hdc);
    return ctx;
}