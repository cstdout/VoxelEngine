#ifndef BLOCKTEXCOORDS_H
#define BLOCKTEXCOORDS_H

#include "src/graphics/mesh/block/blockfacetexcoords.h"
class BlockTexCoords
{
public:
    BlockTexCoords();

    static const uint32_t UV_ARRAY_LENGTH = 48;
    static const uint8_t FACE_COUNT = 6;

    BlockFaceTexCoords frontFace;
    BlockFaceTexCoords backFace;

    BlockFaceTexCoords leftFace;
    BlockFaceTexCoords rightFace;

    BlockFaceTexCoords topFace;
    BlockFaceTexCoords bottomFace;

    BlockFaceTexCoords* faces[FACE_COUNT];

    void front(const char* texPath);
    void front(const std::string& texPath);

    void back(const char* texPath);
    void back(const std::string& texPath);

    void left(const char* texPath);
    void left(const std::string& texPath);

    void right(const char* texPath);
    void right(const std::string& texPath);

    void top(const char* texPath);
    void top(const std::string& texPath);

    void bottom(const char* texPath);
    void bottom(const std::string& texPath);
};

#endif // BLOCKTEXCOORDS_H
