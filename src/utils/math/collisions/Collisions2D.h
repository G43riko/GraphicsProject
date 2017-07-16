//
// Created by gabriel on 24.5.2017.
//

#ifndef GAMEENGINE_COLLISIONS2D_H
#define GAMEENGINE_COLLISIONS2D_H

#include <src/utils/math/objects/Vectors.h>

namespace Collisions2D{
    inline bool pointRect(const Vector2f& point, const Vector2f& rectPosition, const Vector2f& rectSize){
        return point.x > rectPosition.x && point.x < rectPosition.x + rectSize.x &&
               point.y > rectPosition.y && point.y < rectPosition.y + rectSize.y;
    }
    inline bool pointArc(const Vector2f& point, const Vector2f& arcCenter, const float arcRadius){
        return (point - arcCenter).length() < arcRadius;
    }
}

#endif //GAMEENGINE_COLLISIONS2D_H
