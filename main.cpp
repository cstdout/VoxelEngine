#include <iostream>
#include <cstdlib>
#include "src/application.h"
#include "src/window.h"
#include "src/graphics/renderer/chunkrenderer.h"
#include "src/graphics/mesh/world/chunk.h"
#include "src/vectormath/perlinnoise.h"

int main()
{
    uint32_t mapSize = Chunk::WIDTH;

    PerlinNoiseConfig noiseConfig;
    noiseConfig.octaves = 12;
    noiseConfig.offsetX = 0;
    noiseConfig.seed = 0;
    noiseConfig.heightMultiplier = 128;
    PerlinNoise perlinNoise(mapSize);
    perlinNoise.generateNoise(noiseConfig);
//    Image* img = PerlinNoise::noiseToImage(perlinNoise.noise, perlinNoise.getMapSize());
//    img->save("perlinNoise.png", Image::IMG_FORMATS::PNG);


    TextureAtlas texAtlas("assets/textures/blocks/", 256, 256);
    texAtlas.loadFaceTextures();
    texAtlas.buildUVs();
//    texAtlas.textureAtlas->save("atlas.png", Image::PNG);


    TextureConfig config;
    config.minFilter = GL_NEAREST_MIPMAP_LINEAR;
    config.maxFilter = GL_NEAREST;
    Texture tex(texAtlas.textureAtlas, config);


    Chunk chunk(perlinNoise.noise, mapSize * mapSize, &texAtlas);
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
