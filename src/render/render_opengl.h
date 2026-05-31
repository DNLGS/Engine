#ifndef RENDER_OPENGL_H
#define RENDER_OPENGL_H
#include <glad/glad.h>

typedef unsigned int uint;

typedef enum {
    STREAM = GL_STREAM_DRAW,
    STATIC = GL_STATIC_DRAW,
    DYNAMIC = GL_DYNAMIC_DRAW
} BufferUsage;

typedef enum{
    VERTEX = GL_VERTEX_SHADER,
    FRAGMENT = GL_FRAGMENT_SHADER
} ShaderType;

void setViewPort(uint, uint, uint,uint);
void Render(void (*func)(void*), void*);
uint vbo(const float[], uint, BufferUsage);
uint vao();
uint compile_shader(const char*, ShaderType);
uint shader_program();
void attach_shader_program(uint program, const uint shaders[], uint count);

#endif