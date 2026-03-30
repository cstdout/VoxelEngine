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
float PerlinNoise::perlin(float x, float y)
{
    int32_t x0 = int32_t(x);
    int32_t y0 = int32_t(y);
    int32_t x1 = x0 + 1;
    int32_t y1 = y0 + 1;

    float sx = x - float(x0);
    float sy = y - float(y0);


    float n0 = dotGridGradient(x0, y0, x, y);
    float n1 = dotGridGradient(x1, y0, x, y);
    float ix0 = cubicInterpolation(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    float ix1 = cubicInterpolation(n0, n1, sx);

    return cubicInterpolation(ix0, ix1, sy);
}
float PerlinNoise::normalizeFromZeroToOne(float noiseVal)
{
    return noiseVal = (noiseVal / 2.0f) + 0.5f;
}
void PerlinNoise::normalizeFromZeroToOne(float* noiseVal)
{
    (*noiseVal) = ((*noiseVal) / 2.0f) + 0.5f;
}
int32_t PerlinNoise::getRandomNumber(uint32_t seed, int32_t minVal, int32_t maxVal)
{
    srand(seed);
    return (rand() % maxVal) + minVal;
}
