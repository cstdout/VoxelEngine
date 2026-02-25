#include "mesh.h"

Mesh::Mesh()
{

}
Mesh::Mesh(const float* vertices,
           uint32_t size,

           const uint32_t* indices,
           uint32_t indexCount,

           const float* normals,
           uint32_t normalCount)
{
    this->vertices = vertices;
    this->size = size;

    this->indices = indices;
    this->indexCount = indexCount;

    this->normals = normals;
    this->normalCount = normalCount;
}
void Mesh::resetPointers()
{
    this->vertices = nullptr;
    this->size = 0;

    this->indices = nullptr;
    this->indexCount = 0;

    this->normals = nullptr;
    this->normalCount = 0;
}
bool Mesh::verticesExist() const
{
    return (vertices != nullptr && size > 0);
}
bool Mesh::indicesExist() const
{
    return (indices != nullptr && indexCount > 0);
}
bool Mesh::normalsExist() const
{
    return (normals != nullptr && normalCount > 0);
}
