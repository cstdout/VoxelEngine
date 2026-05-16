#ifndef VEC3UINT_H
#define VEC3UINT_H

#include <cstdint>
class Vec3Uint
{
public:
    Vec3Uint();
    Vec3Uint(uint32_t x, uint32_t y, uint32_t z);
    uint32_t x = 0;
    uint32_t y = 0;
    uint32_t z = 0;
};

#endif // VEC3UINT_H
