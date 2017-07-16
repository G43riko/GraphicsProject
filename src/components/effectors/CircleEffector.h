//
// Created by gabriel on 24.5.2017.
//

#ifndef GAMEENGINE_CIRCLEEFFECTOR_H
#define GAMEENGINE_CIRCLEEFFECTOR_H

#include "Effector.h"

#define DEFAULT_CIRCLE_EFFECTOR_DISTANCE 5
#define DEFAULT_CIRCLE_EFFECTOR_SPEED 1.0f

class CircleEffector : public Effector{
    Vector3f _center;
    float _distance;
    Quaternion _rotation;
    Vector3f _direction;
    const float _step;
public:
    inline CircleEffector(Entity& entity,
                          const Vector3f center = Vector3f(),
                          const float distance = DEFAULT_CIRCLE_EFFECTOR_DISTANCE,
                          const float speed = DEFAULT_CIRCLE_EFFECTOR_SPEED,
                          const Vector3f direction = Vector3f(0, 1, 0)) :
            Effector(entity),
            _center(center),
            _distance(distance),
            _direction(direction),
            _step(speed / distance){
        entity.getTransform() -> setPosition(_center + _rotation.getForward() * _distance);
    };

    inline void update(const float delta) override{
        _rotation = Quaternion(Quaternion(_direction, _step).mul(_rotation).normalize());
        _entity.getTransform() -> setPosition(_center + _rotation.getForward() * _distance);
    }
};
#endif //GAMEENGINE_CIRCLEEFFECTOR_H
