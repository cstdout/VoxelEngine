#include "block.h"
#include <iostream>
Block::Block()
{
}
Block::Block(uint32_t blockType)
{
    _blockType = blockType;
}
Block::Block(uint32_t blockType, float x, float y, float z)
{
    _blockType = blockType;
    translate(x, y, z);
}

void Block::setType(uint32_t blockType)
{
    _blockType = blockType;
}
uint32_t Block::getType() const
{
    return _blockType;
}
bool Block::isAir() const
{
    return _blockType == AIR;
}
bool Block::isNotAir() const
{
    return _blockType != AIR;
}
void Block::translate(float x, float y, float z)
{
    this->x += x;
    this->y += y;
    this->z += z;
}
