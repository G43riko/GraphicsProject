//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_HEIGHTGENERATOR_H
#define GRAPHICSPROJECT_HEIGHTGENERATOR_H

#include "src/utils/utils.h"

class HeightGenerator {
    private:
        static constexpr int OCTAVES = 3;
        static constexpr float ROUGHNESS = 0.3f;
        float amplitude;
        int seed;
        int xOffset = 0;
        int zOffset = 0;


    float interpolate(float a, float b, float blend){
            double theta = blend * M_PI;
            float f = (1.0f - cosF(theta)) * 0.5f;
            return a * (1.0f - f) + b * f;
        }
        float getInterpolateNoise(float x, float y){
            unsigned  int intX = (unsigned int)x;
            unsigned int intY = (unsigned int)y;
            float fractX = x - intX;
            float fractY = y - intY;

            float v1 = getSmoothNoise(intX, intY);
            float v2 = getSmoothNoise(intX + 1, intY);
            float v3 = getSmoothNoise(intX, intY + 1);
            float v4 = getSmoothNoise(intX + 1, intY + 1);
            float i1 = interpolate(v1, v2, fractX);
            float i2 = interpolate(v3, v4, fractX);
            return interpolate(i1, i2, fractY);
        }
        float getNoise(unsigned int x, unsigned int y){
            srand(x * 151 + y * 425 + seed);
            return (float)((double)rand() / RAND_MAX) * 2 - 1;
        }
        float getSmoothNoise(unsigned int x, unsigned int y){
            float corners = (getNoise(x - 1, y - 1) + getNoise(x - 1, y + 1) + getNoise(x + 1, y - 1) + getNoise(x + 1 , y + 1)) / 16.0f;
            float sides = (getNoise(x - 1, y) + getNoise(x, y + 1) + getNoise(x, y - 1) + getNoise(x + 1 , y)) / 8.0f;
            float center = getNoise(x, y) / 4.0f;
            return corners + sides + center;
        }
    public:
        HeightGenerator(float amplitude) : HeightGenerator(amplitude, 100000){}
        HeightGenerator(float amplitude, int seed) : amplitude(amplitude), seed(seed){}

        float generateHeight(unsigned int x, unsigned int z){
            /*
            float total =  getInterpolateNoise(x / 4.0f, y / 4.0f) * amplitude;
            total += getInterpolateNoise(x / 2.0f, y / 2.0f) * amplitude / 3.0f;
            total += getInterpolateNoise(x, y) * amplitude / 9.0f;
            return total;
             */
            float total = 0;
            float d = (float) pow(2, OCTAVES-1);
            for(unsigned int i=0;i<OCTAVES;i++){
                float freq = (float) (pow(2, i) / d);
                float amp = (float) pow(ROUGHNESS, i) * amplitude;
                total += getInterpolateNoise((x + xOffset) * freq, (z + zOffset) * freq) * amp;
            }
            return total;
        }
};


#endif //GRAPHICSPROJECT_HEIGHTGENERATOR_H
