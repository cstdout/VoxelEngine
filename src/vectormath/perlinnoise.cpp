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
void PerlinNoise::generateNoise(const PerlinNoiseConfig &noiseConfig, bool shouldNormalizeFromZeroToOne)
{
    float noiseVal;
    float frequency;
    float amplitude;

    uint32_t octaves = noiseConfig.octaves;
    float scale = noiseConfig.scale;
    float lacunarity = noiseConfig.lacunarity;
    float persistance = noiseConfig.persistance;
    uint32_t seed = noiseConfig.seed;

    float offsetX = noiseConfig.offsetX;
    float offsetY = noiseConfig.offsetY;

    if(offsetX < 0)
    {
        offsetX = 0;
    }
    if(offsetY < 0)
    {
        offsetY = 0;
    }

    if(scale <= 0)
    {
        scale = 1e-5f;
    }
    float sampleX;
    float sampleY;
    int32_t maxNumber = 1000;
    int32_t minNumber = 0;
    float randomX;
    float randomY;

    uint32_t index = 0;
    for(uint32_t x = 0; x < mapSize; ++x)
    {
        for(uint32_t y = 0; y < mapSize; ++y)
        {
            noiseVal = 0;
            frequency = 1.0f;
            amplitude = 1.0f;

            for (uint32_t i = 0; i < octaves; ++i)
            {
                randomX = float(PerlinNoise::getRandomNumber(seed, minNumber, maxNumber));
                randomY = float(PerlinNoise::getRandomNumber(seed, minNumber, maxNumber));
                sampleX = (float(x) / scale * frequency) + randomX + offsetX;
                sampleY = (float(y) / scale * frequency) + randomY + offsetY;
                noiseVal += (perlin(sampleX, sampleY) * amplitude);

                frequency *= lacunarity;
                amplitude *= persistance;

            }

            if (noiseVal > 1.0f)
            {
                noiseVal = 1.0f;
            }
            else if (noiseVal < -1.0f)
            {
                noiseVal = -1.0f;
            }
            if(shouldNormalizeFromZeroToOne)
            {
                normalizeFromZeroToOne(&noiseVal);
            }
            noise[index++] = noiseVal;
        }
    }
}
float PerlinNoise::heightCurve(float val, float heightMultiplier)
{
    float s = val * val;
    return (-0.348532f * val + 0.551974f * s + 0.796559f * s * val) * heightMultiplier;
}
