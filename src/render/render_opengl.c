#include "render_opengl.h"

void setViewPort(uint x, uint y, uint width, uint heigth){
    glViewport(x,y,width,heigth);
}

void Render(){
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}