#include "cube.h"

Cube::Cube()
{

}
void Cube::translateVertices(float x, float y, float z, float* res)
{
    uint32_t i = 0;
    while(i < size)
    {
        res[i] = vertices[i] + x;
        ++i;

        res[i] = vertices[i] + y;
        ++i;

        res[i] = vertices[i] + z;
        ++i;
    }
}
