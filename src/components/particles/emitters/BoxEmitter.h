//
// Created by gabriel on 21.5.2017.
//

#ifndef GAMEENGINE_BOXEMITTER_H
#define GAMEENGINE_BOXEMITTER_H

#include "Emitter.h"

class BoxEmitter : public Emitter{
    Vector3f _min, _max;
public:
    inline BoxEmitter(PointerParticleTexture texture,
                      ParticleManager& parent,
                      const float pps,
                      const float speed,
                      const float gravityComplient,
                      const float lifeLength,
                      const Vector3f& min,
                      const Vector3f& max) :
            Emitter(texture, parent, pps, speed, gravityComplient, lifeLength),
            _min(min),
            _max(max){}
    void emitParticle(const Vector3f& center) override{
        Emitter::emitParticle(Vector3f(RANDOMF(_min.x, _max.x), RANDOMF(_min.y, _max.y), RANDOMF(_min.z, _max.z)));
    };
};

#endif //GAMEENGINE_BOXEMITTER_H
