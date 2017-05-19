//
// Created by gabriel on 17.5.2017.
//

#include "Collider.h"
#include "BoundingSphere.h"

IntersectData Collider::intersect(const Collider& other) const{
    if(_type ==TYPE_SPHERE && other._type == TYPE_SPHERE){
        BoudingSphere * self = (BoudingSphere *)this;
        return self ->intersect((BoudingSphere&)other);
    }

    throw "implementácia kolízií ešte nebola dokončená";

    return IntersectData(false, Vector3f());
}