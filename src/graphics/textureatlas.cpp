#include "textureatlas.h"
#include <iostream>

TextureAtlas::TextureAtlas(const char* assetsDir, uint32_t atlasWidth, uint32_t atlasHeight)
{
    init(std::string(assetsDir), atlasWidth, atlasHeight);
}
TextureAtlas::TextureAtlas(const std::string& assetsDir, uint32_t atlasWidth, uint32_t atlasHeight)
{
    init(assetsDir, atlasWidth, atlasHeight);
}
void TextureAtlas::init(const std::string& assetsDir, uint32_t atlasWidth, uint32_t atlasHeight)
{
    this->assetsDir = assetsDir;
    this->texWidth = atlasWidth;
    this->texHeight = atlasHeight;

    BlockTexCoords* grassBlock = new BlockTexCoords;
    grassBlock->front("grass_block_side.png");
    grassBlock->back("grass_block_side.png");

    grassBlock->left("grass_block_side.png");
    grassBlock->right("grass_block_side.png");

    grassBlock->top("grass_block_top.png");
    grassBlock->bottom("dirt.png");

    BlockTexCoords* brickBlock = new BlockTexCoords;
    brickBlock->front("brick.png");
    brickBlock->back("brick.png");

    brickBlock->left("brick.png");
    brickBlock->right("brick.png");

    brickBlock->top("brick.png");
    brickBlock->bottom("brick.png");

    BlockTexCoords* glassBlock = new BlockTexCoords;
    glassBlock->front("glass.png");
    glassBlock->back("glass.png");

    glassBlock->left("glass.png");
    glassBlock->right("glass.png");

    glassBlock->top("glass.png");
    glassBlock->bottom("glass.png");

    BlockTexCoords* oakBlock = new BlockTexCoords;
    oakBlock->front("oak_log.png");
    oakBlock->back("oak_log.png");

    oakBlock->left("oak_log.png");
    oakBlock->right("oak_log.png");

    oakBlock->top("oak_log_top.png");
    oakBlock->bottom("oak_log_top.png");

    BlockTexCoords* missingBlock = new BlockTexCoords;
    missingBlock->front("missing_block.png");
    missingBlock->back("missing_block.png");

    missingBlock->left("missing_block.png");
    missingBlock->right("missing_block.png");

    missingBlock->top("missing_block.png");
    missingBlock->bottom("missing_block.png");


    BlockTexCoords* oakPlanks = new BlockTexCoords;
    oakPlanks->front("oak_planks.png");
    oakPlanks->back("oak_planks.png");

    oakPlanks->left("oak_planks.png");
    oakPlanks->right("oak_planks.png");

    oakPlanks->top("oak_planks.png");
    oakPlanks->bottom("oak_planks.png");

    BlockTexCoords* redStoneLampOnBlock = new BlockTexCoords;
    redStoneLampOnBlock->front("redstone_lamp_on.png");
    redStoneLampOnBlock->back("redstone_lamp_on.png");

    redStoneLampOnBlock->left("redstone_lamp_on.png");
    redStoneLampOnBlock->right("redstone_lamp_on.png");

    redStoneLampOnBlock->top("redstone_lamp_on.png");
    redStoneLampOnBlock->bottom("redstone_lamp_on.png");


    BlockTexCoords* stoneBlock = new BlockTexCoords;
    stoneBlock->front("stone.png");
    stoneBlock->back("stone.png");

    stoneBlock->left("stone.png");
    stoneBlock->right("stone.png");

    stoneBlock->top("stone.png");
    stoneBlock->bottom("stone.png");


    BlockTexCoords* dirtBlock = new BlockTexCoords;
    dirtBlock->front("dirt.png");
    dirtBlock->back("dirt.png");

    dirtBlock->left("dirt.png");
    dirtBlock->right("dirt.png");

    dirtBlock->top("dirt.png");
    dirtBlock->bottom("dirt.png");


    BlockTexCoords* leavesBlock = new BlockTexCoords;
    leavesBlock->front("oak_leaves.png");
    leavesBlock->back("oak_leaves.png");

    leavesBlock->left("oak_leaves.png");
    leavesBlock->right("oak_leaves.png");

    leavesBlock->top("oak_leaves.png");
    leavesBlock->bottom("oak_leaves.png");

    BlockTexCoords* sandBlock = new BlockTexCoords;
    sandBlock->front("sand.png");
    sandBlock->back("sand.png");

    sandBlock->left("sand.png");
    sandBlock->right("sand.png");

    sandBlock->top("sand.png");
    sandBlock->bottom("sand.png");


    BlockTexCoords* waterBlock = new BlockTexCoords;
    waterBlock->front("waterblock.png");
    waterBlock->back("waterblock.png");

    waterBlock->left("waterblock.png");
    waterBlock->right("waterblock.png");

    waterBlock->top("waterblock.png");
    waterBlock->bottom("waterblock.png");


    addBlock(grassBlock);
    addBlock(dirtBlock);
    addBlock(brickBlock);
    addBlock(glassBlock);
    addBlock(oakBlock);
    addBlock(oakPlanks);
    addBlock(leavesBlock);
    addBlock(missingBlock);
    addBlock(redStoneLampOnBlock);
    addBlock(stoneBlock);
    addBlock(sandBlock);
    addBlock(waterBlock);

    textureAtlas = new Image(atlasWidth, atlasHeight, 4);
}
void TextureAtlas::addBlock(BlockTexCoords *uvTexCoords)
{
    blockTexCoords.push_back(uvTexCoords);
    for(uint32_t i = 0; i < BlockTexCoords::FACE_COUNT; ++i)
    {
        allFaces.push_back(uvTexCoords->faces[i]);
    }
}
void TextureAtlas::loadFaceTextures()
{
    std::string texPath;
    Image* img;
    Image* img4Channels;
    size_t faceCount = allFaces.size();

    for(size_t i = 0; i < faceCount; ++i)
    {
        texPath = allFaces.at(i)->texPath;
        if(texPath.empty())
        {
            std::cerr << "TextureAtlas::Empty texture path" << std::endl;
        }
        else
        {
            if(texturePaths.find(texPath) == texturePaths.end())
            {
                img = Image::fromPath(assetsDir + texPath);
                if(img != nullptr && img->bytes != nullptr)
                {
                    texturePaths.insert(texPath);
                    if(img->channels() == 3)
                    {
                        img4Channels = img->addAlphaChannel();
                        Image::freeBytes(img);
                    }
                    else
                    {
                        img4Channels = img;
                    }

                    textures[texPath] = new TextureForFaces(img4Channels, uint32_t(i));
                }
            }
            else
            {
                textures[texPath]->faceIds.push_back(uint32_t(i));
            }
        }
    }
}
void TextureAtlas::buildUVs()
{
    uint32_t xPos = 0, yPos = 0, maxHeight = 0;
    TextureForFaces* loadedTexture;
    Image* img;
    float xStart = 0.0f,
          yStart = 0.0f,
          xEnd = 0.0f,
          yEnd = 0.0f,
          w = float(texWidth),
          h = float(texHeight);

    uint32_t index = 0;
    float* uvs = nullptr;
    for(std::map<std::string, TextureForFaces*>::iterator it = textures.begin(); it != textures.end(); ++it)
    {

        loadedTexture = it->second;
        img = loadedTexture->image;
        if(img->height() > maxHeight)
        {
            maxHeight = img->height();
        }
        if(xPos + img->width() > textureAtlas->width())
        {
            xPos = 0;
            yPos += maxHeight;
            maxHeight = 0;
        }

        textureAtlas->addImage(*img, xPos, yPos);
        xStart = xPos / w;
        yStart = yPos / h;
        xEnd = (xPos + float(img->width())) / w;
        yEnd = (yPos + float(img->height())) / h;
        size_t s = loadedTexture->faceIds.size();
        for(size_t i = 0; i < s; ++i)
        {
            index = 0;
            uvs = allFaces[loadedTexture->faceIds.at(i)]->uvTexCoords;
            uvs[index++] = xStart; uvs[index++] = yEnd;
            uvs[index++] = xEnd;   uvs[index++] = yEnd;
            uvs[index++] = xStart; uvs[index++] = yStart;
            uvs[index++] = xEnd;   uvs[index++] = yStart;

        }

        xPos += img->width();
    }
}
uint32_t TextureAtlas::getWidth() const
{
    return this->texWidth;
}
uint32_t TextureAtlas::getHeight() const
{
    return this->texHeight;
}
TextureAtlas::~TextureAtlas()
{
    allFaces.clear();
    size_t s = blockTexCoords.size();

    for(size_t i = 0; i < s; ++i)
    {
        delete blockTexCoords[i];
    }
    blockTexCoords.clear();
    texturePaths.clear();

    for(std::map<std::string, TextureForFaces*>::iterator it = textures.begin(); it != textures.end(); ++it)
    {
        delete it->second;
    }

    textures.clear();
    delete textureAtlas;
    textureAtlas = nullptr;
}
