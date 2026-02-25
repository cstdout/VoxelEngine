#ifndef MESH_H
#define MESH_H

#include <cstdint>
class Mesh
{
public:
    Mesh();
    Mesh(const float* vertices,
         uint32_t size,

         const uint32_t* indices = nullptr,
         uint32_t indexCount = 0,

         const float* normals = nullptr,
         uint32_t normalCount = 0);

    const float* vertices = nullptr;
    uint32_t size = 0;

    const uint32_t* indices = nullptr;
    uint32_t indexCount = 0;

    const float* normals = nullptr;
    uint32_t normalCount = 0;

    void resetPointers();

    bool verticesExist() const;
    bool indicesExist() const;
    bool normalsExist() const;
};

#endif // MESH_H
