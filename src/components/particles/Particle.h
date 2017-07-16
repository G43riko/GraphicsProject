//
// Created by gabriel on 18.11.2016.
//

#ifndef GRAPHICSPROJECT_PARTICLE_H
#define GRAPHICSPROJECT_PARTICLE_H

#include <src/utils/GUtils.h>
#include "ParticleTexture.h"


class Particle {
    Vector3f position;
    Vector3f velocity;
    //TODO toto su konštanty no častica potom nemože byť vo vectore
    float gravityEffect = 0;
    float lifeLength = 0;
    float rotation = 0;
    float scale = 0;
    PointerParticleTexture texture;
    float elapsedTime = 0;

    Vector2f textureOffset1;
    Vector2f textureOffset2;
    float blend;
    inline void updateTextureCoordInfo(void){
        const float lifeFactor = elapsedTime / lifeLength;
        const int stageCount = texture->getRows() * texture->getColumns();
        const float atlasProgress = lifeFactor * (float)stageCount;
        const int index1 = (int)floor(atlasProgress);
        const int index2 = index1 < stageCount - 1 ? index1 + 1: index1;
        blend = (float)fmod(atlasProgress, 1.0f);

        texture -> setTextureOffset(textureOffset1, index1);
        texture -> setTextureOffset(textureOffset2, index2);
    }
public:
    inline Particle(const PointerParticleTexture texture,
                    const Vector3f &position,
                    const Vector3f &velocity,
                    const float gravityEffect,
                    const float lifeLength,
                    const float rotation,
                    const float scale) :
            position(position),
            velocity(velocity),
            gravityEffect(gravityEffect),
            lifeLength(lifeLength),
            rotation(rotation),
            scale(scale),
            texture(texture){
    }

    inline bool update(const float delta){
        velocity.y += gravityEffect * delta * GRAVITY;
        position += velocity * delta;
        elapsedTime += delta;
        updateTextureCoordInfo();
        return elapsedTime < lifeLength;
    }
    inline Vector3f getPosition(void) const{return position; }
    inline float getRotation(void) const{return rotation; }
    inline float getScale(void) const{ return scale; }
//    inline Vector2f getTextureOffset1(void) const{return textureOffset1;}
//    inline Vector2f getTextureOffset2(void) const{return textureOffset2;}
    inline Vector4f getTextureOffsets(void) const{return Vector4f(textureOffset1.x,
                                                                  textureOffset1.y,
                                                                  textureOffset2.x,
                                                                  textureOffset2.y);}
    inline Vector2f getTextureInfo(void) const{return Vector2f((float)texture -> getRows(), getBlend());}
    inline float getBlend(void) const{return blend;}
    inline PointerParticleTexture getTexture(void) const{return texture; };
};


#endif //GRAPHICSPROJECT_PARTICLE_H
