//
// Created by gabriel on 17.5.2017.
//

#ifndef GAMEENGINE_PLANE_H
#define GAMEENGINE_PLANE_H

#include <src/utils/math/objects/Vectors.h>
#include <src/physics/BoundingSphere.h>
#include <src/physics/Collider.h>

class Plane : public Collider{
    const Vector3f _normal;
    const float _distance;
public:
    inline Plane normalized(void) const{
        const float magnitude = _normal.length();
        return Plane(_normal/magnitude, _distance/magnitude);
    }
    inline IntersectData intersectSphere(const BoudingSphere& other) const{
        const float distanceFromSphereCenter = (float)fabs(_normal.dot(other.getCenter()) + _distance);
        const float distanceFromSphere = distanceFromSphereCenter - other.getRadius();
        return IntersectData(distanceFromSphere < 0, _normal * distanceFromSphere);
    }
    inline Plane(const Vector3f normal, const float distance) :
            Collider(Collider::TYPE_PLANE),
            _normal(normal),
            _distance(distance){};
    inline Vector3f getNormal(void) const{return _normal;}
    inline float getDistance(void) const{return _distance;}
};

#endif //GAMEENGINE_PLANE_H
