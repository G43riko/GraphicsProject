//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_DIRICTIONALLIGHT_H
#define GRAPHICSPROJECT_DIRICTIONALLIGHT_H


#include <src/utils/math/objects/Vectors.h>

class DirectionalLight {
    Vector3f _diffuseColor;
    Vector3f _specularColor = Vector3f(1, 1, 1);
    Vector3f _direction;

    inline DirectionalLight(const Vector3f& diffuseColor, const Vector3f& direction) :
            DirectionalLight(diffuseColor, _specularColor, direction){};

    inline DirectionalLight(const Vector3f& diffuseColor, const Vector3f& specularColor, const Vector3f& direction) :
            _diffuseColor(diffuseColor),
            _specularColor(specularColor),
            _direction(direction){
    }
public:
    inline Vector3f getDirection(void) const{return _direction; }
    inline Vector3f getDiffuseColor(void) const{return _diffuseColor; }
    inline Vector3f getSpecularColor(void) const{return _specularColor; }

    inline void setDirection(Vector3f direction){_direction = direction; };

    inline static PointerDirectionalLight create(Vector3f diffuseColor, Vector3f direction){
        return PointerDirectionalLight(new DirectionalLight(diffuseColor, direction));
    }
    inline static PointerDirectionalLight create(Vector3f diffuseColor, Vector3f specularColor, Vector3f direction){
        return PointerDirectionalLight(new DirectionalLight(diffuseColor, specularColor, direction));
    }

    inline LightData getData(void) const{
        return {LightTypes::DIRECTIONAL,
                {0, 0, 0},
                _diffuseColor.getVec(),
                _specularColor.getVec(),
                {1, 0, 0},
                _direction.getVec(),
                0, 0
        };
    }
};



#endif //GRAPHICSPROJECT_DIRICTIONALLIGHT_H
