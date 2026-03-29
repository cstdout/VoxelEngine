#ifndef BLOCKFACETEXCOORDS_H
#define BLOCKFACETEXCOORDS_H

#include <string>
#include <cstdint>

class BlockFaceTexCoords
{
public:

    BlockFaceTexCoords();
    BlockFaceTexCoords(std::string texturePath);
    BlockFaceTexCoords(const char* texturePath);

    std::string texPath;
    static const uint32_t UV_TEX_COORDS_ARRAY_LENGTH = 8;
    float uvTexCoords[UV_TEX_COORDS_ARRAY_LENGTH] = {};

};

#endif // BLOCKFACETEXCOORDS_H
