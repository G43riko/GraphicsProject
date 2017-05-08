//
// Created by gabriel on 7.5.2017.
//

#ifndef GAMEENGINE_ABSTRACTCHUNK_H
#define GAMEENGINE_ABSTRACTCHUNK_H

#include <src/utils/Vectors.h>

#define CHUNK_SIZE 10

class AbstractChunk{
//    bool isInside = false;
    const int _x, _z;
public:
    inline AbstractChunk(int x, int z) : _x(x), _z(z){};
//    inline bool getInside(void) const{return isInside; };
//    inline void setInside(bool value){isInside = value; };

    inline bool isPosInside(float x, float z) const{
        return x > _x * CHUNK_SIZE && x < (_x + 1) * CHUNK_SIZE &&
               z > _z * CHUNK_SIZE && z < (_z + 1) * CHUNK_SIZE;

    };

    inline int getPosX(void) const{return _x; };
    inline int getPosZ(void) const{return _z; };
    inline std::string getPosString(void) const{return std::to_string(_x) + "_" + std::to_string(_z); };
};
#endif //GAMEENGINE_ABSTRACTCHUNK_H
