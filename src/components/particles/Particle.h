//
// Created by gabriel on 18.11.2016.
//

#ifndef GRAPHICSPROJECT_PARTICLE_H
#define GRAPHICSPROJECT_PARTICLE_H

#include <src/utils/Const.h>
#include <src/utils/Vectors.h>
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

    void setTextreOffset(Vector2f& offset, int index){
        int column = index % texture -> rows;
        int row = index / texture -> rows;
        offset.x = (float) (column / texture -> rows);
        offset.y = (float) (row / texture -> rows);
    }
public:
    Particle(PointerParticleTexture texture, const Vector3f &, const Vector3f &, float, float, float, float);

    bool update(float);
    Vector3f getPosition(void);
    float getRotation(void);
    float getScale(void);

    Vector2f getTextureOffset1(void){
        return textureOffset1;
    }
    Vector2f getTextureOffset2(void){
        return textureOffset2;
    }
    Vector2f getTextureInfo(void){
        return Vector2f((float)getTexture() ->rows, getBlend());
    }

    float getBlend(void){
        return blend;
    }

    PointerParticleTexture getTexture(void){
        return texture;
    };
};


#endif //GRAPHICSPROJECT_PARTICLE_H
