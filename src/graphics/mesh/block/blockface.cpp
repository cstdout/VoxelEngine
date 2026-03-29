#include "blockface.h"

BlockFace::BlockFace()
{

}
BlockFace::BlockFace(int8_t faceType, float x, float y, float z)
{
    init(faceType, x, y, z);
}
BlockFace::~BlockFace()
{
    delete [] vertices;
    vertices = nullptr;
}
void BlockFace::translate(float x, float y, float z)
{
    if(vertices != nullptr)
    {
        uint32_t index = 0;
        while(index < VERTEX_ARRAY_LENGTH)
        {
            vertices[index++] += x;
            vertices[index++] += y;
            vertices[index++] += z;
        }
    }
}
void BlockFace::init(int8_t faceType, float x, float y, float z)
{
    switch (faceType)
    {
        case FaceType::FRONT_FACE:
            vertices = new float[VERTEX_ARRAY_LENGTH]
            {
                -0.5f, -0.5f,  0.5f,
                 0.5f, -0.5f,  0.5f,
                -0.5f,  0.5f,  0.5f,
                 0.5f,  0.5f,  0.5f
            };
        break;
        case FaceType::BACK_FACE:
            vertices = new float[VERTEX_ARRAY_LENGTH]
            {
                0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                0.5f,  0.5f, -0.5f,
                -0.5f,  0.5f, -0.5f
            };
        break;
        case FaceType::LEFT_FACE:
            vertices = new float[VERTEX_ARRAY_LENGTH]
            {
                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f,  0.5f,
                -0.5f,  0.5f, -0.5f,
                -0.5f,  0.5f,  0.5f
            };
        break;

        case FaceType::RIGHT_FACE:
            vertices = new float[VERTEX_ARRAY_LENGTH]
            {
                0.5f, -0.5f,  0.5f,
                0.5f, -0.5f, -0.5f,
                0.5f,  0.5f,  0.5f,
                0.5f,  0.5f, -0.5f
            };
        break;
        case FaceType::TOP_FACE:
            vertices = new float[VERTEX_ARRAY_LENGTH]
            {
                -0.5f,  0.5f,  0.5f,
                0.5f,  0.5f,  0.5f,
                -0.5f,  0.5f, -0.5f,
                0.5f,  0.5f,  -0.5f
            };
        break;
        case FaceType::BOTTOM_FACE:
            vertices = new float[VERTEX_ARRAY_LENGTH]
            {
                -0.5f,  -0.5f,  0.5f,
                0.5f,  -0.5f,  0.5f,
                -0.5f,  -0.5f, -0.5f,
                0.5f,  -0.5f,  -0.5f
            };
        break;
    }
    translate(x, y, z);
}
int32_t BlockFace::getFaceType() const
{
    return _faceType;
}
