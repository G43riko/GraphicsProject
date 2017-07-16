//
// Created by gabriel on 24.5.2017.
//

#ifndef GAMEENGINE_EFFECTOR_H
#define GAMEENGINE_EFFECTOR_H

#include <src/rendering/model/Entity.h>

class Effector{
protected:
    Entity _entity;
public:
    inline Effector(Entity& entity) : _entity(entity){};
    virtual void update(const float delta) = 0;
};

#endif //GAMEENGINE_EFFECTOR_H
