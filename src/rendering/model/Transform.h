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
        Transform(Vector3f *, Vector3f *, Vector3f *);
        void move(float, float, float);

        void rotate(float, float, float);

        Vector3f * getPosition(void);
        float getPosX(void);
        float getPosY(void);
        float getPosZ(void);
        Vector3f * getRotation(void);
        float getRotX(void);
        float getRotY(void);
        float getRotZ(void);
        Vector3f * getScale(void);
        float getScaleX(void);
        float getScaleY(void);
        float getScaleZ(void);
};


#endif //GRAPHICSPROJECT_TRANSFORM_H
