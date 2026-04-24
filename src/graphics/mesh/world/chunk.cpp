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
            for(uint32_t y = 0; y < HEIGHT; ++y)
            {
                blocks[x][z][y].translate(float(x), float(y), float(z));
            }
        }
    }
}

Chunk::Chunk()
{
    init();
}
void Chunk::translate(float x, float y, float z)
{
    for(uint32_t i = 0; i < WIDTH; ++i)
    {
        for(uint32_t k = 0; k < DEPTH; ++k)
        {
            for(uint32_t j = 0; j < HEIGHT; ++j)
            {
                blocks[i][k][j].translate(x, y, z);
            }
        }
    }
    _x += int32_t(x);
    _z += int32_t(z);
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
void Chunk::applyHeightMap(float* heightMap, uint32_t mapSize, TextureAtlas* textureAtlas)
{
    if(mapSize >= getAreaInBlocks())
    {
        this->heightMap = heightMap;
        this->mapSize = mapSize;
        this->textureAtlas = textureAtlas;

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
                    if(j <= 5 && blocks[i][k][j].isAir())
                    {
                        blocks[i][k][j].setType(BlockType::WATER);
                        ++nonTransparentBlocks;
                    }
                }
            }
        }
    }
}
void Chunk::addFaceMesh(const Block* block,
                        int8_t faceType,
                        std::vector<float>& vertices,
                        std::vector<float>& uvs,
                        std::vector<uint32_t>& indices,
                        uint32_t vertexIndex) const
{
    const uint32_t VERTEX_ARRAY_LENGTH = Block::VERTEX_ARRAY_LENGTH;
    const uint32_t UV_TEX_COORDS_ARRAY_LENGTH = BlockFaceTexCoords::UV_TEX_COORDS_ARRAY_LENGTH;

    uint32_t blockType = block->getType();
    BlockFaceTexCoords* face = textureAtlas->blockTexCoords.at(blockType)->faces[faceType];
    for(uint32_t v = 0, u = 0; (v < VERTEX_ARRAY_LENGTH) && (u < UV_TEX_COORDS_ARRAY_LENGTH); v += 3, u += 2)
    {
        vertices.push_back(block->faces[faceType][v] + block->x);
        vertices.push_back(block->faces[faceType][v + 1] + block->y);
        vertices.push_back(block->faces[faceType][v + 2] + block->z);

        uvs.push_back(face->uvTexCoords[u]);
        uvs.push_back(face->uvTexCoords[u + 1]);

    }

    indices.push_back(vertexIndex);
    indices.push_back(vertexIndex + 1);
    indices.push_back(vertexIndex + 2);
    indices.push_back(vertexIndex + 1);
    indices.push_back(vertexIndex + 3);
    indices.push_back(vertexIndex + 2);
}
Mesh* Chunk::buildMesh()
{
    if(!(vertices.empty()))
    {
        vertices.clear();
    }
    if(!(uvs.empty()))
    {
        uvs.clear();
    }
    if(!(indices.empty()))
    {
        indices.clear();
    }

    Mesh* mesh = new Mesh;
    uint32_t maxPossibleSize = nonTransparentBlocks * Block::FACE_COUNT * Block::VERTEX_ARRAY_LENGTH;
    vertices.reserve(maxPossibleSize / 3);


    uint32_t maxPossibleIndexCount = nonTransparentBlocks * Block::FACE_COUNT * 6;
    indices.reserve(maxPossibleIndexCount / 3);

    uint32_t maxPossibleUvSize = nonTransparentBlocks * Block::FACE_COUNT * 8;
    uvs.reserve(maxPossibleUvSize / 3);

    mesh->vertices = vertices.data();
    mesh->indices = indices.data();
    mesh->uvs = uvs.data();
    uint32_t vertexCoordinateIndex = 0;
    uint32_t vertexIndex = 0;
    uint32_t uvIndex = 0;
    uint32_t idx = 0;

    uint32_t blockType = 0;

    const uint32_t VERTEX_ARRAY_LENGTH = Block::VERTEX_ARRAY_LENGTH;
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
                    if(((i == 0)) || (i > 0 && blocks[i - 1][k][j].isAir()))
                    {
                        addFaceMesh(&blocks[i][k][j], LEFT_FACE, vertices, uvs, indices, vertexIndex);
                        vertexCoordinateIndex += VERTEX_ARRAY_LENGTH;
                        uvIndex += UV_TEX_COORDS_ARRAY_LENGTH;
                        idx += 6;
                        vertexIndex += 4;
                    }
                    if((i == (WIDTH - 1)) || ((i < WIDTH - 1) && blocks[i + 1][k][j].isAir()))
                    {
                        addFaceMesh(&blocks[i][k][j], RIGHT_FACE, vertices, uvs, indices, vertexIndex);
                        vertexCoordinateIndex += VERTEX_ARRAY_LENGTH;
                        uvIndex += UV_TEX_COORDS_ARRAY_LENGTH;
                        idx += 6;
                        vertexIndex += 4;
                    }
                    if((j == (HEIGHT - 1)) || ((j < HEIGHT - 1) && blocks[i][k][j + 1].isAir()))
                    {
                        addFaceMesh(&blocks[i][k][j], TOP_FACE, vertices, uvs, indices, vertexIndex);
                        vertexCoordinateIndex += VERTEX_ARRAY_LENGTH;
                        uvIndex += UV_TEX_COORDS_ARRAY_LENGTH;
                        idx += 6;
                        vertexIndex += 4;
                    }
                    if((j == 0) || ((j > 0) && blocks[i][k][j - 1].isAir()))
                    {
                        addFaceMesh(&blocks[i][k][j], BOTTOM_FACE, vertices, uvs, indices, vertexIndex);
                        vertexCoordinateIndex += VERTEX_ARRAY_LENGTH;
                        uvIndex += UV_TEX_COORDS_ARRAY_LENGTH;
                        idx += 6;
                        vertexIndex += 4;
                    }
                    if((k == (DEPTH - 1)) || ((k < DEPTH - 1) && blocks[i][k + 1][j].isAir()))
                    {
                        addFaceMesh(&blocks[i][k][j], FRONT_FACE, vertices, uvs, indices, vertexIndex);
                        vertexCoordinateIndex += VERTEX_ARRAY_LENGTH;
                        uvIndex += UV_TEX_COORDS_ARRAY_LENGTH;
                        idx += 6;
                        vertexIndex += 4;
                    }
                    if(((k == 0)) || ((k > 0) && blocks[i][k - 1][j].isAir()))
                    {
                        addFaceMesh(&blocks[i][k][j], BACK_FACE, vertices, uvs, indices, vertexIndex);
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
