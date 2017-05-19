//
// Created by gabriel on 18.11.2016.
//

#ifndef GRAPHICSPROJECT_PARTICLE_H
#define GRAPHICSPROJECT_PARTICLE_H

#include <src/utils/GConst.h>
#include <src/utils/math/objects/Vectors.h>
#include "ParticleTexture.h"


class Particle {
    private:
        Vector3f position;
        Vector3f velocity;
        float gravityEffect;
        float lifeLength;
        float rotation;
        float scale;
        PointerParticleTexture texture;
        float elapsedTime = 0;

        Vector2f textureOffset1;
        Vector2f textureOffset2;
        float blend;
        void updateTextureCoordInfo(void){
            float lifeFactor = elapsedTime / lifeLength;
            int stageCount = texture->rows * texture->columns;
            float atlasProgress = lifeFactor * (float)stageCount;
            int index1 = (int)floor(atlasProgress);
            int index2 = index1 < stageCount - 1 ? index1 + 1: index1;
            blend = (float)fmod(atlasProgress, 1.0f);

            setTextreOffset(textureOffset1, index1);
            setTextreOffset(textureOffset2, index2);
        }

    inline void setTextreOffset(Vector2f& offset, int index){
        float column = (float)(index % texture -> rows);
        float row = (float)(index / texture -> rows);
        offset.x = column / (float)texture -> rows;
        offset.y = row / (float)texture -> rows;
    }

public:
    inline Particle(PointerParticleTexture texture, const Vector3f &position, const Vector3f &velocity, float gravityEffect, float lifeLength, float rotation, float scale)
            :texture(texture){
        this -> position = position;
        this -> velocity = velocity;
        this -> gravityEffect = gravityEffect;
        this -> lifeLength = lifeLength;
        this -> rotation = rotation;
        this -> scale = scale;
    }

    inline bool update(float delta){
        velocity.y += gravityEffect * delta * GRAVITY;
        position += velocity * delta;
        elapsedTime += delta;
        updateTextureCoordInfo();
        return elapsedTime < lifeLength;
    }
    Vector3f getPosition(void) const{return position; }
    inline float getRotation(void) const{return rotation; }
    inline float getScale(void) const{ return scale; }
    inline Vector2f getTextureOffset1(void) const{return textureOffset1;}
    inline Vector2f getTextureOffset2(void) const{return textureOffset2;}
    inline Vector4f getTextureOffsets(void) const{return Vector4f(textureOffset1.x,
                                                                  textureOffset1.y,
                                                                  textureOffset2.x,
                                                                  textureOffset2.y);}
    inline Vector2f getTextureInfo(void) const{return Vector2f((float)getTexture() ->rows, getBlend());}
    inline float getBlend(void) const{return blend;}
    inline PointerParticleTexture getTexture(void) const{return texture; };
};


#endif //GRAPHICSPROJECT_PARTICLE_H
