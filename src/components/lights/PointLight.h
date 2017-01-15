//
// Created by gabriel on 10.10.2016.
//

#ifndef GRAPHICSPROJECT_LIGHT_H
#define GRAPHICSPROJECT_LIGHT_H


#include <src/utils/Vectors.h>
#include "src/utils/utils.h"
class PointLight {
    public:
        PointLight(Vector3f position, Vector3f color) : PointLight(position, color, attenuation){};
        PointLight(Vector3f position, Vector3f color, Vector3f attenuation) :
                position(position),
                color(color),
                attenuation(attenuation){
        };
        void setPosition(float x, float y, float z){
            position.x = x;
            position.y = y;
            position.z = z;
        };

        Vector3f getPosition(void){
            return position;
        };
        Vector3f getDiffuseColor(void){
            return color;
        };
        Vector3f getSpecularColor(void){
            return specularColor;
        };
        Vector3f getAttenuation(void){
            return attenuation;
        };
    private:
        Vector3f position;
        Vector3f color;
        Vector3f specularColor = Vector3f(1, 1, 1);
        Vector3f attenuation = Vector3f(1, 0, 0);
};

typedef std::shared_ptr<PointLight> PointerPointLight;

PointerPointLight createPointLight(Vector3f, Vector3f);
PointerPointLight createPointLight(Vector3f, Vector3f, Vector3f);

#endif //GRAPHICSPROJECT_LIGHT_H
