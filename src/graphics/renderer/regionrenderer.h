#ifndef REGIONRENDERER_H
#define REGIONRENDERER_H

#include "src/graphics/renderer/meshrenderer.h"
#include "src/graphics/texture.h"
#include "src/graphics/mesh/world/region.h"
#include "src/graphics/mesh/cube.h"


class RegionRenderer : public MeshRenderer
{
public:
    RegionRenderer(const Mesh* mesh, int32_t viewportWidth = 0, int32_t viewportHeight = 0);
    ~RegionRenderer();
    void setTextureAtlas(Texture* atlas)
    {
        _textureAtlas = atlas;
    }
    void setRegion(Region* region)
    {
        _region = region;
        _chunks = region->meshes;
        _chunkCount = region->getAreaInChunks();
    }
    void init();
    void setBackFaceCulling(bool flag)
    {
        this->_backFaceCulling = flag;
    }
    void handleEvents(float delta);


protected:
    Texture* _textureAtlas = nullptr;
    uint32_t _texCoordBuffer = 0;
    void linkUniforms();
    void onDraw(float delta, int32_t w, int32_t h);

    Mesh** _chunks = nullptr;
    uint32_t _chunkCount = 0;
    Region* _region = nullptr;
    void bindChunkData(uint32_t chunkId);
    bool _backFaceCulling = false;

    Vec3 _faceNorm;
    float _selectedCube[Cube::size];
    void _drawCube();
    bool _shouldRenderCube = false;
    Vec3Uint _coordsOfObservingChunk;


    static constexpr char BLOCK_TEXTURE_FRAGMENT_SHADER[] =
        "#version 330 core\n"
        "in vec2 TexCoord;\n"
        "out vec4 FragColor;\n"
        "uniform sampler2D ourTexture;\n"
        "uniform bool isSelected;\n"
        "void main()\n"
        "{\n"
        "   if (isSelected)\n"
        "   {\n"
        "       FragColor = vec4(0.2, 0.2, 0.2, 1.0);\n"
        "   }\n"
        "   else\n"
        "   {\n"
        "       FragColor = texture(ourTexture, TexCoord);\n"
        "   }\n"
        "}\n";
};

#endif // REGIONRENDERER_H
