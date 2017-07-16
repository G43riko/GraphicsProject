//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_WATERTILE_H
#define GRAPHICSPROJECT_WATERTILE_H


class WaterTile {
    const float _x, _z;
    float _height;
    const float _size;
public:
    inline WaterTile(const float x, const float z, const float height, const float size) :
            _x(x),
            _z(z),
            _height(height),
            _size(size){}

    //GETTERS

    inline float getHeight(void) const{return _height; }
    inline float getSize(void) const{return _size; }
    inline float getX(void) const{return _x; }
    inline float getZ(void) const{return _z; }

    //SETTERS

    inline void setHeight(const float height){_height = height; }
};


#endif //GRAPHICSPROJECT_WATERTILE_H
