//
// Created by gabriel on 17.5.2017.
//

#ifndef GAMEENGINE_COLLIDER_H
#define GAMEENGINE_COLLIDER_H

#include <src/physics/IntersectData.h>

class Collider{
    int _type;
public:
    enum{
        TYPE_SPHERE,
        TYPE_AABB,
        TYPE_PLANE,
        TYPE_SIZE
    };
    inline Collider(int type) : _type(type){};
    IntersectData intersect(const Collider& other) const;
    inline Vector3f getCenter(void) const{return Vector3f(0, 0, 0);}
    inline int getType(void) const{return _type;}
};

#endif //GAMEENGINE_COLLIDER_H
