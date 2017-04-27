//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_WATERTILE_H
#define GRAPHICSPROJECT_WATERTILE_H


class WaterTile {
private:
    const float x, z;
    float height;
    const float size;
public:
    inline WaterTile(float centerX, float centerZ, float height, float size) : x(centerX), z(centerZ), height(height), size(size){}

    //GETTERS

    inline float getSize() const{return size; }
    inline float getHeight() const{return height; }
    inline float getX() const{return x; }
    inline float getZ() const{return z; }

    //SETTERS

    inline void setHeight(float height){this -> height = height; }
};


#endif //GRAPHICSPROJECT_WATERTILE_H
