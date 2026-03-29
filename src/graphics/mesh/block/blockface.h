#ifndef BLOCKFACE_H
#define BLOCKFACE_H

#include <cstdint>

enum FaceType
{
    FRONT_FACE = 0,
    BACK_FACE,
    LEFT_FACE,
    RIGHT_FACE,
    TOP_FACE,
    BOTTOM_FACE
};

class BlockFace
{
public:
    BlockFace();
    BlockFace(int8_t faceType, float x = 0, float y = 0, float z = 0);
    ~BlockFace();

    static const uint32_t VERTEX_ARRAY_LENGTH = 12;
    float* vertices = nullptr;
    void translate(float x, float y, float z);

    int32_t getFaceType() const;
private:
    void init(int8_t faceType, float x, float y, float z);
    int8_t _faceType = -1;
};

#endif // BLOCKFACE_H
