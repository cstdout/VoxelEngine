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
