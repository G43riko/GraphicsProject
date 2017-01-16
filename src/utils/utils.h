//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_UTILS_H
#define GRAPHICSPROJECT_UTILS_H

#include <stdlib.h>
#include <set>
#include <math.h>
#include <random>
#include <src/utils/Vectors.h>

class Vector3f;

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


inline float lerp(float a, float b, float f){
    return a + f * (b - a);
}

std::vector<Vector3f> getKerner(void);

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
