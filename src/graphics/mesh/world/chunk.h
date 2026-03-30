#ifndef CHUNK_H
#define CHUNK_H

#include "src/graphics/mesh/block/block.h"
#include "src/graphics/mesh/mesh.h"
#include "src/graphics/textureatlas.h"
class Chunk
{
public:
    static const uint32_t WIDTH = 128;
    static const uint32_t HEIGHT = 16;
    static const uint32_t DEPTH = 128;
    static uint32_t getBlockTotalCount()
    {
        return WIDTH * HEIGHT * DEPTH;
    }
    static uint32_t getAreaInBlocks()
    {
        return WIDTH * DEPTH;
    }
    Chunk();
    Chunk(uint32_t* heightMap,
          uint32_t mapSize,
          TextureAtlas* textureAtlas,
          int32_t x = 0,
          int32_t y = 0,
          int32_t z = 0);
    ~Chunk();
//    Block blocks[WIDTH][DEPTH][HEIGHT];
    Block*** blocks = nullptr;
    Mesh* buildMesh() const;
    TextureAtlas* textureAtlas = nullptr;
    void addFaceMesh(const Block* block,
                     int8_t faceType,
                     float* outVertices,
                     float* outUVs,
                     uint32_t* outIndices,
                     uint32_t vertexIndex = 0) const;
private:
    void init();
    uint32_t* heightMap = nullptr;
    uint32_t mapSize = 0;
    int32_t x = 0;
    int32_t y = 0;
    int32_t z = 0;
    uint32_t nonTransparentBlocks = 0;
};

#endif // CHUNK_H
