#ifndef PERLINNOISE_H
#define PERLINNOISE_H

#include <cstdint>
#include "src/graphics/image.h"


struct PerlinNoiseConfig {
    uint32_t octaves = 12;
    uint32_t seed = 1337;
    float lacunarity = 2.0f;
    float scale = 100.0f;
    float persistance = 0.5f;
    float offsetX = 0;
    float offsetY = 0;

};

class PerlinNoise
{
public:
    PerlinNoise(uint32_t noiseMapSize);
    ~PerlinNoise();
    void generateNoise(const PerlinNoiseConfig& noiseConfig, bool shouldNormalizeFromZeroToOne = true);
    static Image* noiseToImage(float* noise, uint32_t mapSize, bool shouldNormalizeFromZeroToOne = false);
    static float normalizeFromZeroToOne(float noiseVal);
    static void normalizeFromZeroToOne(float* noiseVal);
    static float heightCurve(float val, float heightMultiplier = 1.0f);
    static int32_t getRandomNumber(uint32_t seed, int32_t minVal, int32_t maxVal);
    float* noise = nullptr;
    Image* noiseMap = nullptr;

    static void randomGradient(int32_t x, int32_t y, float* outX, float* outY);
    static float dotGridGradient(int32_t x, int32_t y, float x1, float y1);
    static float cubicInterpolation (float a0, float a1, float w);
    static float perlin(float x, float y);

    uint32_t noiseSize() const
    {
        return noiseArrSize;
    }
    uint32_t getMapSize() const
    {
        return mapSize;
    }
    bool empty() const
    {
        return (noiseArrSize == 0);
    }
private:
    uint32_t noiseArrSize = 0;
    uint32_t mapSize = 0;
};

#endif // PERLINNOISE_H
