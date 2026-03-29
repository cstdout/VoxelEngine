#include "chunk.h"
#include <cmath>

void Chunk::init()
{
    blocks = new Block**[WIDTH];
    for(uint32_t x = 0; x < WIDTH; ++x)
    {
        blocks[x] = new Block*[DEPTH];
        for(uint32_t z = 0; z < DEPTH; ++z)
        {
            blocks[x][z] = new Block[HEIGHT];
        }
    }
}

Chunk::Chunk()
{
    init();
}
Chunk::Chunk(uint32_t* heightMap, uint32_t size, TextureAtlas* textureAtlas, int32_t x, int32_t y, int32_t z)
{
    if(size >= getAreaInBlocks())
    {
        init();
        this->heightMap = heightMap;
        this->mapSize = size;
        this->textureAtlas = textureAtlas;
        this->x = x;
        this->y = y;
        this->z = z;
        uint32_t heightMapIndex = 0;
        float heightMapValue;

        for(uint32_t i = 0; i < WIDTH; ++i)
        {
            for(uint32_t k = 0; k < DEPTH; ++k)
            {
                heightMapValue = heightMap[heightMapIndex++];
                for(uint32_t j = 0; j < HEIGHT; ++j)
                {
                    if(j < heightMapValue)
                    {
                        blocks[i][k][j].setType(BlockType::GRASS);
                        ++nonTransparentBlocks;
                    }
                    blocks[i][k][j].translate(float(i) + float(x),
                                              float(j) + float(y),
                                              float(k) + float(z));
                }
            }
        }
    }
}
