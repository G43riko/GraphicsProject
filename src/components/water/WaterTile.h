//
// Created by gabriel on 7.1.2017.
//

#ifndef GRAPHICSPROJECT_WATERTILE_H
#define GRAPHICSPROJECT_WATERTILE_H


class WaterTile {
    private:
        float height;
        float x, z;
    public:
        float size = 50;
        WaterTile(float centerX, float centerZ, float height){
            this -> x = centerX;
            this -> z = centerZ;
            this -> height = height;
        }

        float getSize(){
            return size;
        }

        void setHeight(float height){
            this -> height = height;
        }

        float getHeight() {
            return height;
        }

        float getX() {
            return x;
        }

        float getZ() {
            return z;
        }
};


#endif //GRAPHICSPROJECT_WATERTILE_H
