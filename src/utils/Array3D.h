//
// Created by gabriel on 2.5.2017.
//

#ifndef GAMEENGINE_ARRAY3D_H
#define GAMEENGINE_ARRAY3D_H

#include <array>
#include <cstdlib>

template <typename T, u_int32_t sizeX, u_int32_t sizeY, u_int32_t sizeZ>
class Array3D{
    const uint32_t _sizeXY = sizeX * sizeY;
    std::array<T, sizeX * sizeY * sizeZ> _array;
public:
    inline T& get(const u_int32_t x, const u_int32_t y, const u_int32_t z) const{
        return _array[z * _sizeXY + y * sizeX + x];
    }
    inline void set(const u_int32_t x, const u_int32_t y, const u_int32_t z, const T& item){
        _array[z * _sizeXY + y * sizeX + x] = item;
    }
    inline void set(const u_int32_t x, const u_int32_t y, const u_int32_t z, const T item){
        _array[z * _sizeXY + y * sizeX + x] = item;
    }
};


#endif //GAMEENGINE_ARRAY3D_H