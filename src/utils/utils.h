//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_UTILS_H
#define GRAPHICSPROJECT_UTILS_H

#include <stdlib.h>
#include <set>
#include <math.h>
#include <random>
#include "Vectors.h"
template<typename T>
inline int sinI(T num){return (int)sin(num); }

template<typename T>
inline float sinF(T num){return (float)sin(num); }

template<typename T>
inline int cosI(T num){return (int)cos(num); }

template<typename T>
inline float cosF(T num){return (float)cos(num); }

template<typename T>
inline bool eq(float a, T b){return !(a < b || a >= b); }

template<typename T>
inline bool gq(float a, T b){return !(a < b || a >= b); }

/*
float lerp(float a, float b, float f){
    return a + f * (b - a);
}

std::vector<Vector3f> getKerner(){
    std::uniform_real_distribution<float> randomFloats(0.0, 1.0);
    std::default_random_engine generator;

    std::vector<Vector3f> ssaoKernel;
    for(int i=0 ; i<64 ; i++){
        float scale = (float)i / 64;
        scale =  lerp(0.1f, 1.0f, scale * scale);
        ssaoKernel.push_back(Vector3f(randomFloats(generator) * 2 - 1, randomFloats(generator) * 2 - 1, randomFloats(generator)).normalize() * randomFloats(generator) * scale);
    }
}
*/

double random(double min, double max);
/*
float randomF(double min, double max){
    return (float)random(min, max);
}

int randomI(double min, double max){
    return (int)random(min, max);
}
*/

class IdGenerator{
    private:
        static int counter;
    public:
        static int getId(void);
};

#endif //GRAPHICSPROJECT_UTILS_H
