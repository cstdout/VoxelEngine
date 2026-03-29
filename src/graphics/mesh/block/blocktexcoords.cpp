#include "blocktexcoords.h"

BlockTexCoords::BlockTexCoords()
{
    faces[0] = &frontFace;
    faces[1] = &backFace;

    faces[2] = &leftFace;
    faces[3] = &rightFace;

    faces[4] = &topFace;
    faces[5] = &bottomFace;
}
void BlockTexCoords::front(const char* texPath)
{
    frontFace.texPath = std::string(texPath);
}
void BlockTexCoords::front(const std::string& texPath)
{
    frontFace.texPath = texPath;
}
void BlockTexCoords::back(const char* texPath)
{
    backFace.texPath = std::string(texPath);
}
void BlockTexCoords::back(const std::string& texPath)
{
    backFace.texPath = texPath;
}
void BlockTexCoords::left(const char* texPath)
{
    leftFace.texPath = std::string(texPath);
}
void BlockTexCoords::left(const std::string& texPath)
{
    leftFace.texPath = texPath;
}
void BlockTexCoords::right(const char* texPath)
{
    rightFace.texPath = std::string(texPath);
}
void BlockTexCoords::right(const std::string& texPath)
{
    rightFace.texPath = texPath;
}
void BlockTexCoords::top(const char* texPath)
{
    topFace.texPath = std::string(texPath);
}
void BlockTexCoords::top(const std::string& texPath)
{
    topFace.texPath = texPath;
}
void BlockTexCoords::bottom(const char* texPath)
{
    bottomFace.texPath = std::string(texPath);
}
void BlockTexCoords::bottom(const std::string& texPath)
{
    bottomFace.texPath = texPath;
}
