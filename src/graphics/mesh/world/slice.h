#ifndef SLICE_H
#define SLICE_H

#include <cstdint>
float* slice(float* array,
             uint32_t arrLen,
             uint32_t rowStart,
             uint32_t rowEnd,
             uint32_t colStart,
             uint32_t colEnd,
             uint32_t* resultSize);

#endif // SLICE_H
