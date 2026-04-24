#ifndef CHUNK_H
#define CHUNK_H

#include "src/graphics/mesh/block/block.h"
#include "src/graphics/mesh/mesh.h"
#include "src/graphics/textureatlas.h"
class Chunk
{
public:
    static const uint32_t WIDTH = 16;
    static const uint32_t HEIGHT = 128;
    static const uint32_t DEPTH = 16;
    static uint32_t getTotalBlockCount()
    {
        return WIDTH * HEIGHT * DEPTH;
    }
    static uint32_t getAreaInBlocks()
    {
        return WIDTH * DEPTH;
    }
    Chunk();
    Chunk(float* heightMap,
          uint32_t mapSize,
          TextureAtlas* textureAtlas,
          int32_t x = 0,
          int32_t y = 0,
          int32_t z = 0);
    ~Chunk();

    Block*** blocks = nullptr;
    void applyHeightMap(float* heightMap, uint32_t mapSize, TextureAtlas* textureAtlas);
    Mesh* buildMesh();
    TextureAtlas* textureAtlas = nullptr;

    void addFaceMesh(const Block* block,
                int8_t faceType,
                std::vector<float>& vertices,
                std::vector<float>& uvs,
                std::vector<uint32_t>& indices,
                uint32_t vertexIndex = 0) const;
    void translate(float x, float y, float z);
    int32_t getX() const
    {
        return _x;
    }
    int32_t getZ() const
    {
        return _z;
    }
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    std::vector<float> uvs;

    Chunk* frontNeighbour = nullptr;
    Chunk* backNeighbour = nullptr;
    Chunk* leftNeighbour = nullptr;
    Chunk* rightNeighbour = nullptr;
private:
    void init();
    float* heightMap = nullptr;
    uint32_t mapSize = 0;
    int32_t _x = 0;
    int32_t _y = 0;
    int32_t _z = 0;
    uint32_t nonTransparentBlocks = 0;

    bool farRightBlockOfLeftNeighbourIsAir(uint32_t localZ, uint32_t localY) const
       {
           if(this->leftNeighbour == nullptr)
           {
               return false;
           }
           if(this->leftNeighbour->blocks == nullptr)
           {
               return false;
           }
           return this->leftNeighbour->blocks[WIDTH - 1][localZ][localY].isAir();
       }
       bool farLeftBlockOfRightNeighbourIsAir(uint32_t localZ, uint32_t localY) const
       {
           if(this->rightNeighbour == nullptr)
           {
               return false;
           }
           if(this->rightNeighbour->blocks == nullptr)
           {
               return false;
           }
           return this->rightNeighbour->blocks[0][localZ][localY].isAir();
       }
       bool farFrontBlockOfBackNeighbourIsAir(uint32_t localX, uint32_t localY) const
       {
           if(this->backNeighbour == nullptr)
           {
               return false;
           }
           if(this->backNeighbour->blocks == nullptr)
           {
               return false;
           }
           return this->backNeighbour->blocks[localX][0][localY].isAir();
       }
       bool farBackBlockOfFrontNeighbourIsAir(uint32_t localX, uint32_t localY) const
       {
           if(this->frontNeighbour == nullptr)
           {
               return false;
           }
           if(this->frontNeighbour->blocks == nullptr)
           {
               return false;
           }
           return this->frontNeighbour->blocks[localX][DEPTH - 1][localY].isAir();
       }
};

#endif // CHUNK_H
