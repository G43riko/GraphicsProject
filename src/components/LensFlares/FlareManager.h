//
// Created by gabriel on 24.5.2017.
//

#ifndef GAMEENGINE_FLAREMANAGER_H
#define GAMEENGINE_FLAREMANAGER_H

#include <vector>
#include <src/core/BasicCamera.h>
#include "FlareTexture.h"

#define CETER_SCREEN {0.5f, 0.5f}
class FlareManager{
    std::vector<FlareTexture*> _textures;
    const float _spacing;

    inline Vector2f static convertToScreenSpace(const Vector3f& worldPos,
                                                const Matrix4f& viewMatrix,
                                                const Matrix4f& projectionMatrix){
        Vector4f coords = Vector4f(worldPos.x, worldPos.y, worldPos.z, 1.0f);
//        Matrix4f transform = Matrix4f::initTranslation(worldPos);
        Matrix4f::transform(viewMatrix, coords, &coords);
        Matrix4f::transform(projectionMatrix, coords, &coords);
        if(coords.w <= 0){
            return Vector2f();
        }
        const float x = (coords.x / coords.w + 1) / 2;
        const float y = (1 - (coords.y / coords.w + 1) / 2);
        return Vector2f(x, y);
    }

    inline void calcFlarePosition(const Vector2f& sunToCenter, const Vector2f& sunCoords){
        ITERATE_VECTOR(_textures, i){
            Vector2f direction = sunToCenter * ((float)i * _spacing);
            Vector2f flarePos = sunCoords + direction;
            _textures[i] -> setPosition(flarePos);
        }
    }
public:
    inline FlareManager(float spacing, std::vector<FlareTexture*>& textures):
            _textures(textures),
            _spacing(spacing){

    }

    void render(BasicCamera camera, const Vector3f& sunPos){
        const Vector2f sunCoords = convertToScreenSpace(sunPos,
                                                        camera.getViewMatrix(),
                                                        Matrix4f(camera.getProjectionMatrix()));
        if(EZ(sunCoords.x) && EZ(sunCoords.y)){
            return;
        }
//        sunCoords.show("coords");
        Vector2f sunToCenter = Vector2f(0.5f, 0.5f) - sunCoords;
        float brihtness = 1 - (sunToCenter.length() / 0.6f);
        if(brihtness > 0){
//            printf("flare: %f\n", brihtness);
            calcFlarePosition(sunToCenter, sunCoords);
        }
    }
};

#endif //GAMEENGINE_FLAREMANAGER_H
