//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_WATERTILE_H
#define GRAPHICSPROJECT_WATERTILE_H


class WaterTile {
private:
    const float _x, _z;
    float _height;
    const float _size;
public:
    inline WaterTile(float x, float z, float height, float size) : _x(x), _z(z), _height(height), _size(size){}

    //GETTERS

    inline float getSize(void) const{return _size; }
    inline float getHeight(void) const{return _height; }
    inline float getX(void) const{return _x; }
    inline float getZ(void) const{return _z; }

    //SETTERS

    inline void setHeight(float height){_height = height; }
};


#endif //GRAPHICSPROJECT_WATERTILE_H
