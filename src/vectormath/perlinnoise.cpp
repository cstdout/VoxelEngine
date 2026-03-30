#include "perlinnoise.h"
#include <cmath>

PerlinNoise::PerlinNoise(uint32_t noiseMapSize)
{
    mapSize = noiseMapSize;
    noiseArrSize = mapSize * mapSize;
    noise = new float[noiseArrSize];
}
void PerlinNoise::randomGradient(int32_t x, int32_t y, float* outX, float* outY)
{
    const uint32_t W = 8 * sizeof(uint32_t);
    const uint32_t S = (W >> 1);
    uint32_t a = uint32_t(x);
    uint32_t b = uint32_t(y);
    a *= 3284157443;

    b ^= a << S | a >> W - S;
    b *= 1911520717;

    a ^= b << S | b >> W - S;
    a *= 2048419325;
    float random = a * (3.14159265f / ~(~0u >> 1)); // in [0, 2*Pi]

    (*outX) = sinf(random);
    (*outY) = cosf(random);
}
float PerlinNoise::dotGridGradient(int32_t x, int32_t y, float x1, float y1)
{
    float gradientX, gradientY;
    randomGradient(x, y, &gradientX, &gradientY);

    float dx = x1 - float(x);
    float dy = y1 - float(y);

    return (dx * gradientX) + (dy * gradientY);
}
float  PerlinNoise::cubicInterpolation (float a0, float a1, float w)
{
    return (a1 - a0) * (3.0f - w * 2.0f) * w * w + a0;
}
