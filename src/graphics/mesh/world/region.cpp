#include "region.h"

Region::Region()
{
    const float CHUNK_WIDTH = float(Chunk::WIDTH);
    const float CHUNK_HEIGHT = float(Chunk::HEIGHT);
    const float CHUNK_DEPTH = float(Chunk::DEPTH);
    chunks = new Chunk**[WIDTH_IN_CHUNKS];
    for(uint32_t i = 0; i < WIDTH_IN_CHUNKS; ++i)
    {
        chunks[i] = new Chunk*[DEPTH_IN_CHUNKS];
        for(uint32_t k = 0; k < DEPTH_IN_CHUNKS; ++k)
        {
            chunks[i][k] = new Chunk[HEIGHT_IN_CHUNKS];
            for(uint32_t j = 0; j < HEIGHT_IN_CHUNKS; ++j)
            {
                chunks[i][k][j].translate(float(i) * CHUNK_WIDTH,
                                          float(j) * CHUNK_HEIGHT,
                                          float(k) * CHUNK_DEPTH);
            }
        }
    }

    meshes = new Mesh*[getAreaInChunks()];
}
uint32_t Region::getTotalBlockCount()
{
    return getTotalChunkCount() * Chunk::getTotalBlockCount();
}
uint32_t Region::getTotalChunkCount()
{
    return WIDTH_IN_CHUNKS * HEIGHT_IN_CHUNKS * DEPTH_IN_CHUNKS;
}
uint32_t Region::getAreaInBlocks()
{
    return getAreaInChunks() * Chunk::getAreaInBlocks();
}
uint32_t Region::getAreaInChunks()
{
    return WIDTH_IN_CHUNKS * DEPTH_IN_CHUNKS;
}
void Region::buildMeshes()
{
    uint32_t index = 0;
    for(uint32_t i = 0; i < WIDTH_IN_CHUNKS; ++i)
    {
        for(uint32_t k = 0; k < DEPTH_IN_CHUNKS; ++k)
        {
            meshes[index++] = chunks[i][k][0].buildMesh();
        }
    }
}
Region::~Region()
{
    for(uint32_t i = 0; i < WIDTH_IN_CHUNKS; ++i)
    {
        for(uint32_t k = 0; k < DEPTH_IN_CHUNKS; ++k)
        {
            delete [] chunks[i][k];
        }
        delete [] chunks[i];
    }
    delete [] chunks;
    chunks = nullptr;
}
