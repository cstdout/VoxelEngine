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
Chunk::~Chunk()
{

    for(uint32_t x = 0; x < WIDTH; ++x)
    {
        for(uint32_t z = 0; z < DEPTH; ++z)
        {
            delete [] blocks[x][z];
        }
        delete [] blocks[x];
    }
    delete [] blocks;
    blocks = nullptr;

    this->heightMap = nullptr;
    mapSize = 0;

    textureAtlas = nullptr;
}
void Chunk::addFaceMesh(const Block* block,
                        int8_t faceType,
                        float* outVertices,
                        float* outUVs,
                        uint32_t* outIndices,
                        uint32_t vertexIndex) const
{
    const uint32_t VERTEX_ARRAY_LENGTH = BlockFace::VERTEX_ARRAY_LENGTH;
    const uint32_t UV_TEX_COORDS_ARRAY_LENGTH = BlockFaceTexCoords::UV_TEX_COORDS_ARRAY_LENGTH;

    uint32_t blockType = block->getType();
    BlockFaceTexCoords* face = textureAtlas->blockTexCoords.at(blockType)->faces[faceType];
    for(uint32_t v = 0, u = 0; (v < VERTEX_ARRAY_LENGTH) && (u < UV_TEX_COORDS_ARRAY_LENGTH); v += 3, u += 2)
    {
        *outVertices = block->faces[faceType]->vertices[v];
        ++outVertices;

        *outVertices = block->faces[faceType]->vertices[v + 1];
        ++outVertices;

        *outVertices = block->faces[faceType]->vertices[v + 2];
        ++outVertices;

        *outUVs = face->uvTexCoords[u];
        ++outUVs;

        *outUVs = face->uvTexCoords[u + 1];
        ++outUVs;
    }

    *outIndices = vertexIndex;
    ++outIndices;

    *outIndices = vertexIndex + 1;
    ++outIndices;

    *outIndices = vertexIndex + 2;
    ++outIndices;

    *outIndices = vertexIndex + 1;
    ++outIndices;

    *outIndices = vertexIndex + 3;
    ++outIndices;

    *outIndices = vertexIndex + 2;
    ++outIndices;
}
