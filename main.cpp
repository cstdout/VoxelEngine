#include <iostream>
#include <cstdlib>
#include "src/application.h"
#include "src/window.h"
#include "src/graphics/renderer/chunkrenderer.h"
#include "src/graphics/mesh/world/chunk.h"


int main()
{
    TextureAtlas texAtlas("assets/textures/blocks/", 256, 256);
    texAtlas.loadFaceTextures();
    texAtlas.buildUVs();
    texAtlas.textureAtlas->save("atlas.png", Image::PNG);


    TextureConfig config;
    config.minFilter = GL_NEAREST;
    config.maxFilter = GL_NEAREST;
    Texture tex(texAtlas.textureAtlas, config);

    uint32_t elemCount = Chunk::getAreaInBlocks();
    uint32_t* heightMap = new uint32_t[elemCount];
    srand(NULL);
    for(int i = 0; i < elemCount; ++i)
    {
        heightMap[i] = rand() % 16;
    }
    Chunk chunk(heightMap, elemCount, &texAtlas);
    Mesh* mesh = chunk.buildMesh();

    const int32_t WINDOW_WIDTH = 720;
    const int32_t WINDOW_HEIGHT = 680;


    ChunkRenderer chunkRenderer(mesh, WINDOW_WIDTH, WINDOW_HEIGHT);
    chunkRenderer.setTextureAtlas(&tex);

    Window w(WINDOW_WIDTH, WINDOW_HEIGHT, "My Window");
    w.setCursorDisabled(true);

    Application app;
    app.setWindow(&w);
    app.setRenderer(&chunkRenderer);

    app.run();

    return 0;
}
