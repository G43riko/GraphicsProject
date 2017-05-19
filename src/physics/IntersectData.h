//
// Created by gabriel on 17.5.2017.
//

#ifndef GAMEENGINE_INTERSECTDATA_H
#define GAMEENGINE_INTERSECTDATA_H

#include <src/utils/math/objects/Vectors.h>

class IntersectData{
    const bool _intersect;
//    const float _distance;
    const Vector3f _direction;
public:
    inline IntersectData(const bool ntersect, const Vector3f direction) : _intersect(ntersect), _direction(direction){};
    inline bool isIntersect(void) const{return _intersect; }
    inline float getDistance(void) const{return _direction.length(); }
    inline const Vector3f& getDirection(void) const{return _direction; }
};

#endif //GAMEENGINE_INTERSECTDATA_H
