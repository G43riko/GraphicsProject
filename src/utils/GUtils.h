//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_UTILS_H
#define GRAPHICSPROJECT_UTILS_H

#include <stdlib.h>
#include <set>
#include <math.h>
#include <random>
#include <iostream>
#include "GTypes.h"

#define SET_IF_IS_NULL(el, val) if(el == nullptr){el = val; }

#define CHECK_AND_SET(x, y) {if(x != nullptr){x = y;}}
#define CHECK_AND_CALL(x, y) {if(x != nullptr){x -> y;}}
#define CHECK_AND_CLEAR(el) \
    if(IS_NOT_NULL(el)){    \
        el -> cleanUp();    \
        delete el;          \
        el = nullptr;       \
    }
#define CHECK_AND_DEL(el)   \
    if(IS_NOT_NULL(el)){    \
        delete el;          \
        el = nullptr;       \
    }

/*******************************************STRINGS*******************************************/

#define C_STRING_START_WITH(x, y) (strstr(x, y) == x ? 1 : 0)
#define C_STRING_CONTAINS(x, y) (strstr(x, y) != NULL ? 1 : 0)

#define STRING_START_WITH(x, y) (x.find(y) == 0)
#define STRING_END_WITH(x, y) (x.size() >= y.size() && x.compare(x.size() - y.size(), y.size(), y) == 0)
#define STRING_CONTAINS(x, y) (x.find(y) != std::string::npos)

/*******************************************OUTPUT*******************************************/

#define ERROR(x) std::cerr << x << ": " <<  __FILE__ << " > " << __FUNCTION__ << " > " <<  __LINE__ << std::endl
#define PRINT(x) std::cout << x << std::endl
#define DEBUG(x) //std::cerr << x << std::endl


/*******************************************ITERATOR*******************************************/

//#define MAP_CONTAINS_KEY(map, key) (map.find(key) != map.end())
#define MAP_CONTAINS_KEY(map, key) (!map.empty() && map.count(key) > 0)
#define ITERATE_VECTOR(x, y) for(long unsigned int y=0, __j__=x.size() ; y<__j__ ; y++)
#define ITERATE_VECTOR_ITERATOR_AUTO_ENDLESS(x, y) for(auto y = x.begin() ; y != x.end();)
#define ITERATE_VECTOR_ITERATOR_AUTO(x, y) for(auto y = x.begin() ; y != x.end(); ++y)
#define ITERATE_VECTOR_ITERATOR(x, y, z) for(z y = x.begin() ; y != x.end() ; ++y)
#define ITERATE_MAP_AUTO(x, y) for(auto y = x.begin() ;  y != x.end() ; ++y)
#define ITERATE_MAP(x, y, z) for(z y = x.begin() ; y != x.end() ; ++y)


/*******************************************COMPARATORS*******************************************/

#define IS_NULL(x) (x == nullptr)
#define IS_NOT_NULL(x) (x != nullptr)

//Equal
#define EQ(a, b) !(a < b || a > b)


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

#define GABS(x) ((x) < 0 ? -(x) : (x))
#define GMIN(a, b) ((a) < (b) ? (a) : (b))
#define GMAX(a, b) ((a) > (b) ? (a) : (b))

#define GFLOOR(x) ((x) < 0.0 ? (int)(x) - 1 : (int)(x)) //22.5.2017

#define GCLAMP(a, b, c) (a < b ? b : a > c ? c : a);

#define SIGNUM(x) ((x) > 0 ? 1 : (x) < 0 ? -1 : 0)

//Linerar Interpolation
#define LERP(a, b, c) ((b) + ((a) - (b)) * (c))

#define LOOP(x, y) for(int y = 0 ; y < x ; y++)
#define LOOP_EQ(x, y) for(int y = 0 ; y <= x ; y++)
#define LOOP_U(x, y) for(uint y = 0 ; y < x ; y++)
#define LOOP_U_EQ(x, y) for(uint y = 0 ; y <= x ; y++)

#define SINI (a) (int)sin(num)
#define SINF(a) (float)sin(a)

#define COSI(a) (int)cos(num)
#define COSF(a) (float)cos(a)

/*******************************************UTILS******************************************************/

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(*a))

//macro ako náhrada pre new
//použitie: GNEW(Vector3f, 2, 3, 4)
#define GNEW(X, ...) (new (malloc(sizeof(X))) X(__VA_ARGS__))

#define GSWAP(t, x, y)  {t temp = x; x = y; y = temp;} // 22.5.2017

/*******************************************OTHERS******************************************************/


template<typename T, typename ...Args>
inline std::unique_ptr<T> make_unique( Args&& ...args ) {
    return std::unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}

#define RANDOMI(LO, HI) static_cast<int>(LO + static_cast<int>(rand()) / (static_cast<int>(RAND_MAX / (HI - LO))))
#define RANDOMF(LO, HI) static_cast<float>(LO + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / (HI - LO)))
#define RANDOM(LO, HI) (LO + rand() / (RAND_MAX / (HI - LO)))

inline double grandom(double LO, double HI){
    return RANDOMF(LO, HI);
}
/*
inline VectorV3 getKerner(void){
    std::uniform_real_distribution<float> randomFloats(0.0, 1.0);
    std::default_random_engine generator;

    VectorV3 ssaoKernel;
    for(int i=0 ; i<64 ; i++){
        float scale = (float)i / 64;
        scale =  LERP(0.1f, 1.0f, scale * scale);
        Vector3f sample = Vector3f(randomFloats(generator) * 2 - 1, randomFloats(generator) * 2 - 1, randomFloats(generator)).normalize();
        sample *= randomFloats(generator) * scale;
        ssaoKernel.push_back(sample);
    }
    return ssaoKernel;
}
*/
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