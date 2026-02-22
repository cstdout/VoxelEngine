#include "vertexattributeobject.h"
#include <iostream>
VertexAttributeObject::VertexAttributeObject()
{
}
void VertexAttributeObject::unbind() const
{

}
void VertexAttributeObject::bind() const
{
    if(id > 0)
    {
        glBindVertexArray(id);
    }
    else
    {
        std::cerr << "VAO was not created" << std::endl;
    }
}
void VertexAttributeObject::create()
{
    glGenVertexArrays(1, &id);
}
void VertexAttributeObject::deleteVAO()
{
    if(id > 0)
    {
        glDeleteVertexArrays(1, &id);
        id = 0;
    }
    else
    {
        std::cerr << "VAO was not created" << std::endl;
    }
}
VertexAttributeObject::~VertexAttributeObject()
{
    if(id > 0)
    {
        deleteVAO();
    }

}
