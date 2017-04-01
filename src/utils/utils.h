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


#define ERROR(x) std::cerr << x << std::endl
#define PRINT(x) std::cout << x << std::endl
#define DEBUG(x) //std::cerr << x << std::endl

#define SINI (a) (int)sin(num)
#define SINF(a) (float)sin(a)
#define COSI(a) (int)cos(num)
#define COSF(a) (float)cos(a)

//Equal
#define EQ(a, b) !(a < b || a > b)

//Not Equal
#define NEQ(a, b) !EQ(a, b)

//Equal Zero
#define NZ(a) EQ(a, 0)

//Not Equal Zero
#define NEZ(a) !NZ(a)

//Linerar Interpolation
#define LERP(a, b, c) (a + c * (b - a));

class Vector3f;
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
