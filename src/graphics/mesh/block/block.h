#ifndef BLOCK_H
#define BLOCK_H

#include "src/graphics/mesh/block/blockface.h"


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

class Block
{
public:

    Block();
    Block(uint32_t blockType);
    Block(uint32_t blockType, float x, float y, float z);
    void translate(float x, float y, float z);

    BlockFace front{FaceType::FRONT_FACE};
    BlockFace back{FaceType::BACK_FACE};
    BlockFace left{FaceType::LEFT_FACE};
    BlockFace right{FaceType::RIGHT_FACE};
    BlockFace top{FaceType::TOP_FACE};
    BlockFace bottom{FaceType::BOTTOM_FACE};

    static const uint8_t FACE_COUNT = 6;
    BlockFace* faces[FACE_COUNT] = {};
    void setType(uint32_t blockType);
    uint32_t getType() const
    {
        return _blockType;
    }
    bool isAir() const
    {
        return _blockType == AIR;
    }
    bool isNotAir() const
    {
        return _blockType != AIR;
    }
private:
    uint32_t _blockType = AIR;
    void init();
};

#endif // BLOCK_H
