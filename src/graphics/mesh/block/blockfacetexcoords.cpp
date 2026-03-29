#include "blockfacetexcoords.h"

BlockFaceTexCoords::BlockFaceTexCoords()
{
}
BlockFaceTexCoords::BlockFaceTexCoords(std::string texturePath)
{
    texPath = texturePath;
}
BlockFaceTexCoords::BlockFaceTexCoords(const char* texturePath)
{
    texPath = std::string(texturePath);
}
