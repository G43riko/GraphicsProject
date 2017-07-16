//
// Created by gabriel on 24.5.2017.
//

#ifndef GAMEENGINE_FROMTOEFFECTOR_H
#define GAMEENGINE_FROMTOEFFECTOR_H

#include "Effector.h"

#define DEFAULT_FROM_TO_EFFECTOR_SPEED 0.1f

class FromToEffector : public Effector{
    const Vector3f _a;
    const Vector3f _b;
    float _value = 0.0f;
    float _step;
public:
    inline FromToEffector(const Vector3f& a,
                          const Vector3f& b,
                          Entity& target,
                          const float speed = DEFAULT_FROM_TO_EFFECTOR_SPEED) :
            Effector(target),
            _a(a),
            _b(b),
            _step(1.0f / (float)GFLOOR((_a - _b).length() / speed)){};

    inline void update(const float delta) override{
        _entity.getTransform() -> setPosition(Vector3f::interpolate(_a, _b, _value));
        _value += _step;
        if(_value <= 0 || _value >= 1){
            _step = -_step;
        }
    }
};

#endif //GAMEENGINE_FROMTOEFFECTOR_H
