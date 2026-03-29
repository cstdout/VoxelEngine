#include "textureatlas.h"

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

    textureAtlas = new Image(atlasWidth, atlasHeight, 4);
}
