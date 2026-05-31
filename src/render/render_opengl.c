#include "render_opengl.h"
#include <stdio.h>
#include "../shader/shader_reader.h"
#include <stdlib.h>

void setViewPort(uint x, uint y, uint width, uint heigth){
    glViewport(x,y,width,heigth);
}

void Render(void (*func)(), void* data){
    if (func != NULL)
        func(data);
}

uint vbo(const float data[], uint size, BufferUsage bufferusage){
    uint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, size, data, bufferusage);  

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0);  

    return vbo;
}

uint vao(){
    uint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    return vao;
}

uint compile_shader(const char* source, ShaderType type){
    uint shader;
    shader = glCreateShader(type);
    
    char* value = load_file(source);     
    const char* codigo_constante = value;
    glShaderSource(shader, 1, &codigo_constante, NULL);
    
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::COMPILATION_FAILED\n %s\n", infoLog);
    };

    free(value); 
    return shader;
}

uint shader_program(){
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    
    return shaderProgram;
}

void attach_shader_program(uint program, const uint shaders[], uint count){
    for (size_t i = 0; i < count; i++)
        glAttachShader(program, shaders[i]);

    glLinkProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::PROGRAM::LINK_FAILED\n%s\n", infoLog);
    }

    for (size_t i = 0; i < count; i++)
        glDeleteShader(shaders[i]); // pode deletar APÓS linkar
}