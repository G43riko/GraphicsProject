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

#define SET_IF_IS_NULL(el, val) \
if(el == nullptr){              \
    el = val;                   \
}

#define CHECK_AND_CLEAR(el) \
    if(el){                 \
        el -> cleanUp();    \
        delete el;          \
        el = nullptr;       \
    }

#define ERROR(x) std::cerr << x << ": " <<  __FILE__ << " > " << __FUNCTION__ << " > " <<  __LINE__ << std::endl
#define PRINT(x) std::cout << x << std::endl
#define DEBUG(x) //std::cerr << x << std::endl

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*a))

#define SINI (a) (int)sin(num)
#define SINF(a) (float)sin(a)
#define COSI(a) (int)cos(num)
#define COSF(a) (float)cos(a)

#ifndef ABS
    #define ABS(x) (x < 0 ? -x : x)
#endif

//macro ako náhrada pre new
//použitie: GNEW(Vector3f, 2, 3, 4)
#define GNEW(X, ...) (new (malloc(sizeof(X))) X(__VA_ARGS__))

//Equal
#define EQ(a, b) !(a < b || a > b)

#define IS_NULL(x) (x == nullptr)
#define IS_NOT_NULL(x) (x != nullptr)

//Not Equal
#define NEQ(a, b) !EQ(a, b)

//Equal Zero
#define EZ(a) EQ(a, 0)

//Not Equal Zero
#define NEZ(a) !EZ(a)

/*******************************************MATH******************************************************/
#define MATH_PI 3.1415926535897932384626433832795
#define TO_RADIANS(x) (float)((x) * MATH_PI / 180.0f)
#define TO_DEGREES(x) (float)((x) * 180.0f / MATH_PI)

#ifndef MAX
    #define MIN (a, b) a < b ? a : b
#endif

#ifndef MAX
    #define MAX (a, b) a > b ? a : b
#endif

#ifndef CLAMP
    #define CLAMP(a, b, c) (a < b ? b : a > c ? c : a);
#endif


//Linerar Interpolation
#define LERP(a, b, c) (a + c * (b - a));

/*******************************************OTHERS******************************************************/

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

/**
 * Objekt bude počítať vytvorené inštancie
 */
class CountedObj {
public:
    CountedObj() {++total_;}
    CountedObj(const CountedObj& obj) {if(this != &obj) ++total_;}
    ~CountedObj() {--total_;}

    static size_t OustandingObjects() {return total_;}
private:
    static size_t total_;
};

#endif //GRAPHICSPROJECT_UTILS_H
