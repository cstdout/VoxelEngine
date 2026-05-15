#include "region.h"
#include "slice.h"
#include <float.h>

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

    for(uint32_t i = 0; i < WIDTH_IN_CHUNKS; ++i)
    {
        for(uint32_t k = 0; k < DEPTH_IN_CHUNKS; ++k)
        {
            for(uint32_t j = 0; j < HEIGHT_IN_CHUNKS; ++j)
            {
                if(k < (DEPTH_IN_CHUNKS - 1))
                {
                    chunks[i][k][j].backNeighbour = &chunks[i][k + 1][j];
                }
                if(k > 0)
                {
                    chunks[i][k][j].frontNeighbour = &chunks[i][k - 1][j];
                }
                if(i < (WIDTH_IN_CHUNKS - 1))
                {
                    chunks[i][k][j].rightNeighbour = &chunks[i + 1][k][j];
                }
                if(i > 0)
                {
                    chunks[i][k][j].leftNeighbour = &chunks[i - 1][k][j];
                }
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
void Region::applyHeightMap(float *heightMap, uint32_t mapSize, TextureAtlas* textureAtlas)
{
    if(mapSize >= getAreaInBlocks())
    {
        uint32_t chunkNum = 0;
        for(uint32_t i = 0; i < WIDTH_IN_CHUNKS; ++i)
        {
            for(uint32_t k = 0; k < DEPTH_IN_CHUNKS; ++k)
            {
                uint32_t resultSize;
                float* slicedHeightMap = slice(heightMap,
                                               mapSize,
                                               i * Chunk::WIDTH,
                                               (i + 1) * Chunk::WIDTH,
                                               k * Chunk::DEPTH,
                                               (k + 1) * Chunk::DEPTH,
                                               &resultSize);
                for(uint32_t j = 0; j < HEIGHT_IN_CHUNKS; ++j)
                {
                    chunks[i][k][j].applyHeightMap(slicedHeightMap, resultSize, textureAtlas);
                }
                delete [] slicedHeightMap;
            }
        }
    }
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
Block* Region::getBlock(uint32_t x, uint32_t y, uint32_t z) const
{
    uint32_t chunkX = x / Chunk::WIDTH;
    uint32_t chunkY = y / Chunk::HEIGHT;
    uint32_t chunkZ = z / Chunk::DEPTH;
    if(chunkX >= WIDTH_IN_CHUNKS || chunkY >= HEIGHT_IN_CHUNKS || chunkZ >= DEPTH_IN_CHUNKS)
    {
        return nullptr;
    }

    uint32_t blockX = x - chunkX * Chunk::WIDTH;
    uint32_t blockY = y - chunkY * Chunk::HEIGHT;
    uint32_t blockZ = z - chunkZ * Chunk::DEPTH;

    if(blockX >= Chunk::WIDTH || blockY >= Chunk::HEIGHT || blockZ >= Chunk::DEPTH)
    {
        return nullptr;
    }
    return &(chunks[chunkX][chunkZ][chunkY].blocks[blockX][blockZ][blockY]);
}
Block* Region::rayCast(const Vec3& start,
                       const Vec3& dir,
                       Vec3& norm,
                       uint32_t maxDistance) const
{
    Block* block = nullptr;
    if(dir.isNull())
    {
        return nullptr;
    }


    float startX = start.v[0];
    float startY = start.v[1];
    float startZ = start.v[2];

    float dirX = 2 * dir.v[0];
    float dirY = 2 * dir.v[1];
    float dirZ = 2 * dir.v[2];

    float t = 0.5f;
    uint32_t x, y, z;
    while(t <= maxDistance)
    {
        x = uint32_t(startX + t * dirX + 0.5f);
        y = uint32_t(startY + t * dirY + 0.5f);
        z = uint32_t(startZ + t * dirZ + 0.5f);
        block = getBlock(x, y, z);
        if(block != nullptr && block->isNotAir())
        {
            return block;
        }
        t += 0.5f;
    }
    return nullptr;
}
