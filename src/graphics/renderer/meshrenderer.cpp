#include <iostream>
#include "meshrenderer.h"

MeshRenderer::MeshRenderer(const Mesh* mesh, int32_t viewportWidth, int32_t viewportHeight)
{
    _viewportWidth = viewportWidth;
    _viewportHeight = viewportHeight;
    _mesh = mesh;
}
MeshRenderer::~MeshRenderer()
{
    if(_vertexBuffer)
    {
        glDeleteBuffers(1, &_vertexBuffer);
    }
    if(_indexBuffer)
    {
        glDeleteBuffers(1, &_indexBuffer);
    }
}
void MeshRenderer::setShader(Shader *shader)
{
    _shader = shader;
}
void MeshRenderer::initVertexBuffer(int32_t vertexCoordInputLocation)
{
    glGenBuffers(1, &_vertexBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, _vertexCount * sizeof(float), _mesh->vertices, GL_STATIC_DRAW);


    glEnableVertexAttribArray(vertexCoordInputLocation);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glVertexAttribPointer(vertexCoordInputLocation, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
}
void MeshRenderer::initUniformMatrices()
{
    unsigned int uniformBlockIndexBlue = glGetUniformBlockIndex(_shader->id(), "Matrices");
    glUniformBlockBinding(_shader->id(), uniformBlockIndexBlue, 0);

    // Now actually create the buffer
    glGenBuffers(1, &_uboMatrices);
    glBindBuffer(GL_UNIFORM_BUFFER, _uboMatrices);
    glBufferData(GL_UNIFORM_BUFFER, 2 * Mat4::sizeInBytes, NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    // define the range of the buffer that links to a uniform binding point
    glBindBufferRange(GL_UNIFORM_BUFFER, 0, _uboMatrices, 0, 2 * Mat4::sizeInBytes);

    // store the projection matrix (we only do this once now) (note: we're not using zoom anymore by changing the FoV)
    Mat4::perspective(45.0f, float(_viewportWidth) / float(_viewportHeight), 0.1f, 100.0f, _projection);
    glBindBuffer(GL_UNIFORM_BUFFER, _uboMatrices);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, Mat4::sizeInBytes, _projection.valuePtr());
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

}
void MeshRenderer::initModel()
{
    _model = Mat4(1.0f);
}
void MeshRenderer::initCamera()
{
    _camera.init(&_viewMatrix, Vec3(0.0f, 0.0f, 3.0f));
}
void MeshRenderer::initIndexBuffer()
{
    glGenBuffers(1, &_indexBuffer);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indexCount * sizeof(uint32_t),  _mesh->indices , GL_STATIC_DRAW);
}
void MeshRenderer::init()
{

    if(_shader == nullptr)
    {
        _shader = new Shader(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER);
    }
    bool shaderIsValid = (_shader && _shader->compile() && _shader->isValid());
    if(_mesh != nullptr && _mesh->verticesExist() && shaderIsValid)
    {
        VAO.create();
        VAO.bind();
        if (_offScreenRenderingMode)
        {
            FBO.create();
            initFramebufferOutputTexture(_viewportWidth, _viewportHeight);
        }


        glEnable(GL_DEPTH_TEST);

        _vertexCount = _mesh->size;

        initVertexBuffer(_shader->getAttribLocation("aPos"));
        initUniformMatrices();
        initModel();
        initCamera();
        if(_mesh->indicesExist())
        {
            _indexCount = _mesh->indexCount;
            initIndexBuffer();
        }


        _initialized = true;
    }
}
void MeshRenderer::linkUniforms()
{
    _shader->setUniformMatrix4fv("model", _model.valuePtr());
}
