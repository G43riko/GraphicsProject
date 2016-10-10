//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_TRANSFORM_H
#define GRAPHICSPROJECT_TRANSFORM_H

#include "../../utils/Vectors.h"

class Transform {
    private:
        PointerVector3f position;
        PointerVector3f rotation;
        PointerVector3f scale;
    public:
        Transform(PointerVector3f, PointerVector3f, PointerVector3f);
        void move(float, float, float);

        void rotate(float, float, float);

        PointerVector3f getPosition(void);
        float getPosX(void);
        float getPosY(void);
        float getPosZ(void);
        PointerVector3f getRotation(void);
        float getRotX(void);
        float getRotY(void);
        float getRotZ(void);
        PointerVector3f getScale(void);
        float getScaleX(void);
        float getScaleY(void);
        float getScaleZ(void);
};


#endif //GRAPHICSPROJECT_TRANSFORM_H
