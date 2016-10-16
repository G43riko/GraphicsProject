//
// Created by gabriel on 15.10.2016.
//

#ifndef GRAPHICSPROJECT_MATH_H
#define GRAPHICSPROJECT_MATH_H


class Math {
    static float linearInterpolation(float a, float b, float val){
        return a * val + (1 - val) * b;
    }
};


#endif //GRAPHICSPROJECT_MATH_H
