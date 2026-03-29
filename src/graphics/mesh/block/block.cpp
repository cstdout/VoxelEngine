#include "block.h"

Block::Block()
{
    init();
}
Block::Block(uint32_t blockType)
{
    _blockType = blockType;
    init();
}
Block::Block(uint32_t blockType, float x, float y, float z)
{
    _blockType = blockType;
    init();
    translate(x, y, z);

}
void Block::init()
{
    faces[FaceType::FRONT_FACE] = &front;
    faces[FaceType::BACK_FACE] = &back;
    faces[FaceType::LEFT_FACE] = &left;
    faces[FaceType::RIGHT_FACE] = &right;
    faces[FaceType::TOP_FACE] = &top;
    faces[FaceType::BOTTOM_FACE] = &bottom;
}
void Block::translate(float x, float y, float z)
{
    for(uint8_t i = 0; i < FACE_COUNT; ++i)
    {
        faces[i]->translate(x, y, z);
    }
}
void Block::setType(uint32_t blockType)
{
    _blockType = blockType;
}
