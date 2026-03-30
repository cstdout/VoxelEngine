#include "perlinnoise.h"

PerlinNoise::PerlinNoise(uint32_t noiseMapSize)
{
    mapSize = noiseMapSize;
    noiseArrSize = mapSize * mapSize;
    noise = new float[noiseArrSize];
}
