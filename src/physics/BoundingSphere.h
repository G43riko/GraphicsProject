//
// Created by gabriel on 17.5.2017.
//

#ifndef GAMEENGINE_BOUNDINGSPHERE_H
#define GAMEENGINE_BOUNDINGSPHERE_H

#include <src/utils/math/objects/Vectors.h>
#include <src/physics/IntersectData.h>
#include <src/physics/Collider.h>

class BoudingSphere : public Collider{
    const Vector3f _center;
    const float _radius;
public:
    inline BoudingSphere(const Vector3f center, const float radius) :
            Collider(Collider::TYPE_SPHERE),
            _center(center),
            _radius(radius){};
    IntersectData intersectBoundingSphere(const BoudingSphere& other) const{
        const float radiusDistance = _radius   + other._radius;
        Vector3f direction = other._center - _center;
        const float centerDistance = direction.length();
        direction /= centerDistance;
        const float distance = centerDistance - radiusDistance;
        return IntersectData(centerDistance < radiusDistance, direction * distance);
    }
    inline Vector3f getCenter(void) const{return _center;}
    inline float getRadius(void) const{return _radius;}
};

#endif //GAMEENGINE_BOUNDINGSPHERE_H
