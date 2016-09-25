//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_TRANSFORM_H
#define GRAPHICSPROJECT_TRANSFORM_H

#include "../../utils/Vectors.h"

class Transform {
    private:
        Vector3f * position;
        Vector3f * rotation;
        Vector3f * scale;
    public:
        Transform(Vector3f * position, Vector3f * rotation, Vector3f * scale) {
            this -> position = position;
            this -> rotation = rotation;
            this -> scale = scale;
        }
        void move(float x, float y, float z){
            position -> x += x;
            position -> y += y;
            position -> z += z;
        }

        void rotate(float x, float y, float z){
            rotation -> x += x;
            rotation -> y += y;
            rotation -> z += z;
        }

        Vector3f * getPosition(void){return position;}
        float getPosX(void){return position -> x;}
        float getPosY(void){return position -> y;}
        float getPosZ(void){return position -> z;}
        Vector3f * getRotation(void){return rotation;}
        float getRotX(void){return rotation -> x;}
        float getRotY(void){return rotation -> y;}
        float getRotZ(void){return rotation -> z;}
        Vector3f * getScale(void){return scale;}
        float getScaleX(void){return scale -> x;}
        float getScaleY(void){return scale -> y;}
        float getScaleZ(void){return scale -> z;}
};


#endif //GRAPHICSPROJECT_TRANSFORM_H
