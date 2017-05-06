//
// Created by gabriel on 2.5.2017.
//

#ifndef GAMEENGINE_ARRAY3D_H
#define GAMEENGINE_ARRAY3D_H

#include <array>
#include <cstdlib>

template <typename T, u_int32_t sizeX, u_int32_t sizeY, u_int32_t sizeZ>
class Array3D{
public:
    T& get(u_int32_t x, u_int32_t y, u_int32_t z){
        return _array[z * _sizeXY + y * sizeX + x];
    }
    void set(u_int32_t x, u_int32_t y, u_int32_t z, T& item){
        _array[z * _sizeXY + y * sizeX + x] = item;
    }
    void set(u_int32_t x, u_int32_t y, u_int32_t z, T item){
        _array[z * _sizeXY + y * sizeX + x] = item;
    }
private:
    const uint32_t _sizeXY = sizeX * sizeY;
    std::array<T, sizeX * sizeY * sizeZ> _array;
};
#endif //GAMEENGINE_ARRAY3D_H
