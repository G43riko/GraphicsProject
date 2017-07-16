//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_HEIGHTGENERATOR_H
#define GRAPHICSPROJECT_HEIGHTGENERATOR_H

//#include "src/utils/GUtils.h"

#define HEIGHT_GENERATOR_OCTAVES 3
#define HEIGHT_GENERATOR_ROUGHNESS 0.3f
#define HEIGHT_GENERATOR_SEED 100000

class HeightGenerator {
    const float amplitude;
    const int seed;
    int xOffset = 0;
    int zOffset = 0;

    inline float interpolate(const float a, const float b, const float blend) const{
        const double theta = blend * M_PI;
        const float f = (1.0f - COSF(theta)) * 0.5f;
        return a * (1.0f - f) + b * f;
    }
    inline float getInterpolateNoise(const float x, const float y) const{
        const uint intX = (uint)x;
        const uint intY = (uint)y;
        const float fractX = x - (float)intX;
        const float fractY = y - (float)intY;

        const float v1 = getSmoothNoise(intX, intY);
        const float v2 = getSmoothNoise(intX + 1, intY);
        const float v3 = getSmoothNoise(intX, intY + 1);
        const float v4 = getSmoothNoise(intX + 1, intY + 1);
        const float i1 = interpolate(v1, v2, fractX);
        const float i2 = interpolate(v3, v4, fractX);
        return interpolate(i1, i2, fractY);
    }
    inline float getNoise(const uint x, const uint y) const{
        srand(x * 151 + y * 425 + seed);
        return (float)((double)rand() / RAND_MAX) * 2 - 1;
    }
    inline float getSmoothNoise(const uint x, const uint y) const{
        const float corners = (getNoise(x - 1, y - 1) +
                               getNoise(x - 1, y + 1) +
                               getNoise(x + 1, y - 1) +
                               getNoise(x + 1, y + 1)) / 16.0f;
        const float sides = (getNoise(x - 1, y) +
                             getNoise(x, y + 1) +
                             getNoise(x, y - 1) +
                             getNoise(x + 1 , y)) / 8.0f;

        const float center = getNoise(x, y) / 4.0f;

        return corners + sides + center;
    }
public:
    inline HeightGenerator(const float amplitude) :
            HeightGenerator(amplitude, HEIGHT_GENERATOR_SEED){}

    inline HeightGenerator(const float amplitude, const int seed) :
            amplitude(amplitude),
            seed(seed){}

    /**
     * Vráti číslo od -1 po 1 vždy rovnaké pre daný bod
     *
     * @param x
     * @param z
     * @return
     */
    inline float generateHeight(const int x, const int z) const{
        float total = 0;
        const float d = (float) pow(2, HEIGHT_GENERATOR_OCTAVES - 1);
        for(uint i=0 ; i<HEIGHT_GENERATOR_OCTAVES ; i++){
            const float freq = (float) (pow(2, i) / d);
            const float amp = (float) pow(HEIGHT_GENERATOR_ROUGHNESS, i) * amplitude;
            total += getInterpolateNoise((float)(x + xOffset) * freq, (float)(z + zOffset) * freq) * amp;
        }
        return total;
    }
};


#endif //GRAPHICSPROJECT_HEIGHTGENERATOR_H
