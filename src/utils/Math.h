//
// Created by gabriel on 15.10.2016.
//

#ifndef GRAPHICSPROJECT_MATH_H
#define GRAPHICSPROJECT_MATH_H


#define MATH_PI 3.1415926535897932384626433832795
#define ToRadians(x) (float)(((x) * MATH_PI / 180.0f))
#define ToDegrees(x) (float)(((x) * 180.0f / MATH_PI))

template<typename T>
inline T clamp(const T &a, const T &min, const T &max) {
    if (a < min) return min;
    else if (a > max) return max;
    else return a;
}

template<typename T>
inline T linearInterpolation(const T &a, const T &b, const T &val){
    return a * val + (1 - val) * b;
}

#endif //GRAPHICSPROJECT_MATH_H
