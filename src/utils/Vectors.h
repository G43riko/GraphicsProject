//
// Created by gabriel on 22.9.2016.
//

#ifndef GRAPHICSPROJECT_VECTORS_H
#define GRAPHICSPROJECT_VECTORS_H

class Vector2f{
    public:
        float x, y;
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
