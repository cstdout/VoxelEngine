#ifndef VERTEXATTRIBUTEOBJECT_H
#define VERTEXATTRIBUTEOBJECT_H

#include <cstdint>
class VertexAttributeObject
{
public:
    VertexAttributeObject();
    void create();
    void deleteVAO();

    void bind() const;
    void unbind() const;

    uint32_t id = 0;
};

#endif // VERTEXATTRIBUTEOBJECT_H
