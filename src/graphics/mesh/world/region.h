#ifndef REGION_H
#define REGION_H

#include "chunk.h"
#include "src/vectormath/vec3.h"
#include "src/vectormath/vec3uint.h"

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

    Block* getBlock(uint32_t x, uint32_t y, uint32_t z, Vec3Uint& chunkCoords) const;
    Block* rayCast(const Vec3& start,
                   const Vec3& dir,
                   Block** prevBlock,
                   Vec3Uint& chunkCoords,
                   uint32_t maxDistance = 6) const;

    void updateChunkNeighbourhood(uint32_t chunkX, uint32_t chunkY, uint32_t chunkZ);
};

#endif // REGION_H
