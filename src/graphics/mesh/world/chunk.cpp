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
Chunk::Chunk(float* heightMap, uint32_t size, TextureAtlas* textureAtlas, int32_t x, int32_t y, int32_t z)
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
                    if(j == 0)
                    {
                        blocks[i][k][j].setType(BlockType::SAND);
                        ++nonTransparentBlocks;
                    }
                    else if(j < heightMapValue)
                    {
                        if(j < 5)
                        {
                            blocks[i][k][j].setType(BlockType::STONE);
                            ++nonTransparentBlocks;
                        }
                        else if(j >= 5)
                        {
                            if(j + 1 < uint32_t(heightMapValue) && (j + 1) < HEIGHT)
                            {
                                blocks[i][k][j].setType(BlockType::DIRT);
                                ++nonTransparentBlocks;
                            }
                            else if(blocks[i][k][j - 1].getType() == BlockType::DIRT)
                            {
                                blocks[i][k][j].setType(BlockType::GRASS);
                                ++nonTransparentBlocks;
                            }
                        }



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
Mesh* Chunk::buildMesh() const
{

    Mesh* mesh = new Mesh;
    uint32_t size = nonTransparentBlocks * Block::FACE_COUNT * BlockFace::VERTEX_ARRAY_LENGTH;
    float* vertices = new float[size];

    uint32_t indexCount = nonTransparentBlocks * Block::FACE_COUNT * 6;
    uint32_t* indices = new uint32_t[indexCount];

    uint32_t uvSize = nonTransparentBlocks * Block::FACE_COUNT * 8;
    float* uvs = new float[uvSize];

    mesh->vertices = vertices;
    mesh->indices = indices;
    mesh->uvs = uvs;
    uint32_t vertexCoordinateIndex = 0;
    uint32_t vertexIndex = 0;
    uint32_t uvIndex = 0;
    uint32_t idx = 0;

    uint32_t blockType = 0;

    const uint32_t VERTEX_ARRAY_LENGTH = BlockFace::VERTEX_ARRAY_LENGTH;
    const uint32_t UV_TEX_COORDS_ARRAY_LENGTH = BlockFaceTexCoords::UV_TEX_COORDS_ARRAY_LENGTH;


    for(uint32_t i = 0; i < WIDTH; ++i)
    {
        for(uint32_t k = 0; k < DEPTH; ++k)
        {
            for(uint32_t j = 0; j < HEIGHT; ++j)
            {
                blockType = blocks[i][k][j].getType();
                if(blocks[i][k][j].isNotAir())
                {
                    if((i == 0) || (i > 0 && blocks[i - 1][k][j].isAir()))
                    {
                        addFaceMesh(&blocks[i][k][j], LEFT_FACE, vertices + vertexCoordinateIndex, uvs + uvIndex, indices + idx, vertexIndex);
                        vertexCoordinateIndex += VERTEX_ARRAY_LENGTH;
                        uvIndex += UV_TEX_COORDS_ARRAY_LENGTH;
                        idx += 6;
                        vertexIndex += 4;
                    }
                    if((i == (WIDTH - 1)) || ((i < WIDTH - 1) && blocks[i + 1][k][j].isAir()))
                    {
                        addFaceMesh(&blocks[i][k][j], RIGHT_FACE, vertices + vertexCoordinateIndex, uvs + uvIndex, indices + idx, vertexIndex);
                        vertexCoordinateIndex += VERTEX_ARRAY_LENGTH;
                        uvIndex += UV_TEX_COORDS_ARRAY_LENGTH;
                        idx += 6;
                        vertexIndex += 4;
                    }
                    if((j == (HEIGHT - 1)) || ((j < HEIGHT - 1) && blocks[i][k][j + 1].isAir()))
                    {
                        addFaceMesh(&blocks[i][k][j], TOP_FACE, vertices + vertexCoordinateIndex, uvs + uvIndex, indices + idx, vertexIndex);
                        vertexCoordinateIndex += VERTEX_ARRAY_LENGTH;
                        uvIndex += UV_TEX_COORDS_ARRAY_LENGTH;
                        idx += 6;
                        vertexIndex += 4;
                    }
                    if((j == 0) || ((j > 0) && blocks[i][k][j - 1].isAir()))
                    {
                        addFaceMesh(&blocks[i][k][j], BOTTOM_FACE, vertices + vertexCoordinateIndex, uvs + uvIndex, indices + idx, vertexIndex);
                        vertexCoordinateIndex += VERTEX_ARRAY_LENGTH;
                        uvIndex += UV_TEX_COORDS_ARRAY_LENGTH;
                        idx += 6;
                        vertexIndex += 4;
                    }
                    if((k == (DEPTH - 1)) || ((k < DEPTH - 1) && blocks[i][k + 1][j].isAir()))
                    {
                        addFaceMesh(&blocks[i][k][j], FRONT_FACE, vertices + vertexCoordinateIndex, uvs + uvIndex, indices + idx, vertexIndex);
                        vertexCoordinateIndex += VERTEX_ARRAY_LENGTH;
                        uvIndex += UV_TEX_COORDS_ARRAY_LENGTH;
                        idx += 6;
                        vertexIndex += 4;
                    }
                    if((k == 0) || ((k > 0) && blocks[i][k - 1][j].isAir()))
                    {
                        addFaceMesh(&blocks[i][k][j], BACK_FACE, vertices + vertexCoordinateIndex, uvs + uvIndex, indices + idx, vertexIndex);
                        vertexCoordinateIndex += VERTEX_ARRAY_LENGTH;
                        uvIndex += UV_TEX_COORDS_ARRAY_LENGTH;
                        idx += 6;
                        vertexIndex += 4;
                    }
                }

            }
        }
    }

    mesh->size = vertexCoordinateIndex;
    mesh->uvSize = uvIndex;
    mesh->indexCount = idx;
    return mesh;
}
