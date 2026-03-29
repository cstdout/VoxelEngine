#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H

#include <vector>
#include <map>
#include <set>
#include "src/graphics/mesh/block/blocktexcoords.h"
#include "src/graphics/image.h"


struct TextureForFaces
{
    Image* image = nullptr;
    std::vector<uint32_t> faceIds;
    TextureForFaces(Image* img, uint32_t id)
    {
        image = img;
        faceIds.push_back(id);
    }
    ~TextureForFaces()
    {
        faceIds.clear();
        image = nullptr;
    }
};
class TextureAtlas
{
public:
    TextureAtlas(const char* assetsDir, uint32_t atlasWidth, uint32_t atlasHeight);
    TextureAtlas(const std::string& assetsDir, uint32_t atlasWidth, uint32_t atlasHeight);
    ~TextureAtlas();
    std::vector<BlockTexCoords*> blockTexCoords;
    std::vector<BlockFaceTexCoords*> allFaces;
    std::map<std::string, TextureForFaces*> textures;
    std::set<std::string> texturePaths;
    std::string assetsDir;

    Image* textureAtlas = nullptr;

    void init(const std::string& assetsDir, uint32_t atlasWidth, uint32_t atlasHeight);
    void addBlock(BlockTexCoords* uvTexCoords);
    void loadFaceTextures();
    void buildUVs();

    uint32_t getWidth() const;
    uint32_t getHeight() const;
private:
    uint32_t texWidth = 0;
    uint32_t texHeight = 0;
};

#endif // TEXTUREATLAS_H
