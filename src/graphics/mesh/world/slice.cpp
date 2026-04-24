#include "slice.h"
#include <cmath>
float* slice(float* array,
             uint32_t arrLen,
             uint32_t rowStart,
             uint32_t rowEnd,
             uint32_t colStart,
             uint32_t colEnd,
             uint32_t* resultSize)
{
    if(rowStart > rowEnd)
    {
        return nullptr;
    }
    if(colStart > colEnd)
    {
        return nullptr;
    }
    uint32_t size = uint32_t(sqrt(arrLen));
    uint32_t startIndex = rowStart * (size - 1) + colStart;
    uint32_t endIndex = rowEnd * (size - 1) + colEnd;
    if(startIndex > arrLen || endIndex > arrLen)
    {
        return nullptr;
    }
    uint32_t sliceSize = (rowEnd - rowStart) * (colEnd - colStart);
    float* result = new float[sliceSize];
    uint32_t resultIndex = 0;
    for(uint32_t i = rowStart; i < rowEnd; ++i)
    {
        for(uint32_t j = colStart; j < colEnd; ++j)
        {
            result[resultIndex++] = array[i * size + j];
        }
    }
    *resultSize = sliceSize;
    return result;

}
