//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_VECTORS_H
#define GRAPHICSPROJECT_VECTORS_H

#include <iostream>
class Vector2f{
    public:
        float x, y;
        Vector2f(int, int);
        Vector2f(float, float);
        Vector2f(float);
        Vector2f(const Vector2f&);
};
class Vector3f{
    public:
        float x, y, z;
        Vector3f(float, float, float);

        Vector3f(float);
        Vector3f(const Vector3f&);
        Vector3f * normalize(void);
        Vector3f * getNormal(void);
        Vector3f * cross(Vector3f *);
        Vector3f * getCross(Vector3f *);
        Vector3f * mul(Vector3f *);
        Vector3f * mul(float);
        Vector3f * getMul(Vector3f *);
        Vector3f * getMul(float);
        void show(void);
};
class Vector4f{
    public:
        float x, y, z, w;
        Vector4f(float, float, float, float);
        Vector4f(float);
        Vector4f(const Vector4f&);
};

class Matrix4f{
    public:
        float x, y, z;
};

#endif //GRAPHICSPROJECT_VECTORS_H
