#ifndef REGION_H
#define REGION_H

#include "chunk.h"
class Region
{
public:
    static const uint32_t WIDTH_IN_CHUNKS = 32;
    static const uint32_t DEPTH_IN_CHUNKS = 32;
    static const uint32_t HEIGHT_IN_CHUNKS = 1;
    Region();
    void applyHeightMap(float* heightMap, uint32_t mapSize, TextureAtlas* textureAtlas);
    void buildMeshes();
    ~Region();
    Mesh** meshes = nullptr;
    Chunk*** chunks = nullptr;
    static uint32_t getTotalChunkCount();
    static uint32_t getTotalBlockCount();
    static uint32_t getAreaInBlocks();
    static uint32_t getAreaInChunks();
};

#endif // REGION_H
