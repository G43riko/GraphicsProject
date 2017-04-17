//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_WATERTILE_H
#define GRAPHICSPROJECT_WATERTILE_H


class WaterTile {
private:
    float size;
    float height;
    float x, z;
public:
    WaterTile(float centerX, float centerZ, float height, float size){
        this -> x = centerX;
        this -> z = centerZ;
        this -> size = size;
        this -> height = height;
    }

    //GETTERS

    float getSize(){ return size; }
    float getHeight() { return height; }
    float getX() { return x; }
    float getZ() { return z; }

    //SETTERS

    void setHeight(float height){ this -> height = height; }
};


#endif //GRAPHICSPROJECT_WATERTILE_H
