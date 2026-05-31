#ifndef MATH_H
#define MATH_H

typedef struct {
    float x, y;
} Vector2;

typedef struct {
    float x, y, z;
} Vector3;

typedef struct {
    float x, y, z, w;
} Vector4;

typedef struct {
    float m[4][4];
} Matrix4;

// vertex.h
typedef struct {
    Vector3 position;
    Vector3 normal;
    Vector2 texcoord;
    Vector4 color;
} Vertex;

typedef struct {
    Vertex* vertices;
    unsigned int* indices;
    int vertex_count;
    int index_count;
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
} Mesh;

#endif


