#include "block.h"

Block::Block()
{
    vertices = new float[VERTEX_ARR_LENGTH]
    {

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f
    };
    size = VERTEX_ARR_LENGTH;

    indices = new uint32_t[INDEX_ARR_LENGTH]
    {
        // Front face
        0, 1, 2,
        1, 3, 2,

        // Back face
        4, 6, 5,
        5, 6, 7,

        // Left face
        0, 2, 4,
        2, 6, 4,

        // Right face
        1, 5, 3,
        5, 7, 3,

        // Top face
        2, 3, 6,
        3, 7, 6,

        // Bottom face
        0, 4, 1,
        4, 5, 1
    };
    indexCount = INDEX_ARR_LENGTH;
}
Block::~Block()
{
    delete [] indices;
    delete [] vertices;

    resetPointers();
}
