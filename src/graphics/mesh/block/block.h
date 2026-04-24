#ifndef BLOCK_H
#define BLOCK_H

#include <cstdint>

enum BlockType
{
    GRASS = 0,
    DIRT,
    BRICK,
    GLASS,
    OAK,
    OAK_PLANKS,
    OAK_LEAVES,
    MISSING,
    RED_STONE_LAMP_ON,
    STONE,
    SAND,
    WATER,
    AIR
};
enum FaceType
{
    FRONT_FACE = 0,
    BACK_FACE,
    LEFT_FACE,
    RIGHT_FACE,
    TOP_FACE,
    BOTTOM_FACE
};
class Block
{
public:

    Block();
    Block(uint32_t blockType);
    Block(uint32_t blockType, float x, float y, float z);

    static const uint32_t VERTEX_ARRAY_LENGTH = 12;

    static inline const float FRONT_FACE[] =
    {
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f
    };

    static inline const float BACK_FACE[] =
    {
        0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f
    };

    static inline const float LEFT_FACE[] =
    {
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f
    };
    static inline const float RIGHT_FACE[] =
    {
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f
    };
    static inline const float TOP_FACE[] =
    {
        -0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  -0.5f
    };
    static inline const float BOTTOM_FACE[] =
    {
        -0.5f,  -0.5f,  0.5f,
        0.5f,  -0.5f,  0.5f,
        -0.5f,  -0.5f, -0.5f,
        0.5f,  -0.5f,  -0.5f
    };

    static const uint8_t FACE_COUNT = 6;
    static inline const float* faces[FACE_COUNT] =
    {
        FRONT_FACE,
        BACK_FACE,
        LEFT_FACE,
        RIGHT_FACE,
        TOP_FACE,
        BOTTOM_FACE
    };
    void setType(uint32_t blockType);
    uint32_t getType() const;
    bool isAir() const;
    bool isNotAir() const;
    void translate(float x, float y, float z);


    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
private:
    uint32_t _blockType = AIR;
};

#endif // BLOCK_H
