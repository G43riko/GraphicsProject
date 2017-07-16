//
// Created by gabriel on 17.5.2017.
//

#ifndef GAMEENGINE_AABB_H
#define GAMEENGINE_AABB_H

#include <src/utils/math/objects/Vectors.h>
#include <src/physics/IntersectData.h>
#include <src/physics/Collider.h>

class AABB : public Collider{
    Vector3f _min;
    Vector3f _max;
public:
    inline IntersectData intersectAABB(const AABB& other) const{
        const Vector3f distance1 = other._min - _max;
        const Vector3f distance2 = _min - other._max;
        const Vector3f distance = distance1.max(distance2);
        const float maxDistance = distance.max();
        return IntersectData(maxDistance < 0, distance);
    };

    inline AABB(const Vector3f& min, const Vector3f& max) :
            Collider(Collider::TYPE_AABB),
            _min(min),
            _max(max){};

    inline Vector3f getMin(void) const{return _min;}
    inline Vector3f getMax(void) const{return _max;}
};

#endif //GAMEENGINE_AABB_H
