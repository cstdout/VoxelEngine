#ifndef CUBE_H
#define CUBE_H

#include <cstdint>
class Cube
{
public:
    Cube();
    static inline const float vertices[] =
    {
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f
    };
    static const uint32_t size = 24;

    static inline const uint32_t indices[] =
    {
        0, 1,  1, 2,  2, 3,  3, 0,
        4, 5,  5, 6,  6, 7,  7, 4,
        0, 4,  1, 5,  2, 6,  3, 7
    };
    static const uint32_t indexCount = 24;

    static void translateVertices(float x, float y, float z, float* res);
};

#endif // CUBE_H
