#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "src/graphics/shader.h"
#include "src/graphics/camera.h"
#include "src/graphics/mesh/mesh.h"


class MeshRenderer : public Renderer
{
public:
    MeshRenderer(const Mesh* mesh, int32_t viewportWidth = 0, int32_t viewportHeight = 0);
    ~MeshRenderer();
    static constexpr char DEFAULT_VERTEX_SHADER[] =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 aTexCoord;\n"
        "out vec2 TexCoord;"
        "layout (std140) uniform Matrices\n"
        "{\n"
        "   mat4 projection;\n"
        "   mat4 view;\n"
        "};\n"
        "uniform mat4 model;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
        "   TexCoord = aTexCoord;\n"
        "}\n";
    static constexpr char DEFAULT_TEXTURE_FRAGMENT_SHADER[] =
        "#version 330 core\n"
        "in vec2 TexCoord;\n"
        "out vec4 FragColor;\n"
        "uniform sampler2D ourTexture;\n"
        ""
        "void main()\n"
        "{\n"
        "   FragColor = texture(ourTexture, TexCoord);\n"
        "}\n";
    static constexpr char DEFAULT_FRAGMENT_SHADER[] =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(0.0, 0.0, 1.0, 1.0);\n"
        "}\n";
    void init();
    void setShader(Shader* shader);

protected:
    void onDraw(float delta, int32_t w, int32_t h);
    virtual void linkUniforms();
    Shader* _shader = nullptr;

    uint32_t _vertexBuffer = 0;
    uint32_t _uboMatrices = 0;

    Mat4 _projection;
    Mat4 _model;
    Mat4 _viewMatrix;

    Camera _camera;

    uint32_t _indexBuffer = 0;
    uint32_t _indexCount = 0;

    const Mesh* _mesh;
    uint32_t _vertexCount;

    void initVertexBuffer(int32_t vertexCoordInputLocation = 0);
    void initUniformMatrices();
    virtual void initModel();
    void initCamera();
    void initIndexBuffer();

};

#endif // MESHRENDERER_H
