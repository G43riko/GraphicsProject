//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_MATERIAL_H
#define GRAPHICSPROJECT_MATERIAL_H

#include <memory>
#include "Texture2D.h"
#include "CubeTexture.h"

class Material {
    PointerCubeTexture _environmentalMap    = nullptr;
    PointerTexture2D _diffuse               = nullptr;
    PointerTexture2D _specular              = nullptr;
    PointerTexture2D _normal                = nullptr;
    PointerTexture2D _alpha                 = nullptr;
    PointerTexture2D _bump                  = nullptr;

    float _shineDumber = DEFAULT_MATERIAL_SHINE_DUMPER;
    float _reflectivity = DEFAULT_MATERIAL_REFLECTIVITY;

    inline Material(PointerTexture2D diffuse, PointerTexture2D normal = nullptr) :
            _diffuse(diffuse),
            _normal(normal){};
public:
    inline bool hasEnvironmentalMap(void) const{return IS_NULL(_environmentalMap); };

    //GETTERS
    inline PointerCubeTexture getEnvironmentalMap(void) const{return _environmentalMap; };
    inline PointerTexture2D getSpecular(void) const{return _specular;};
    inline PointerTexture2D getDiffuse(void) const{return _diffuse;};
    inline PointerTexture2D getNormal(void) const{return _normal;};
    inline PointerTexture2D getAlpha(void) const{return _alpha;};
    inline PointerTexture2D getBump(void) const{return _bump;};

    inline float getReflectivity(void) const{return _reflectivity; };
    inline float getShineDumper(void) const{return _shineDumber; };

    //SETTERS

    inline void setEnvironmentalMap(PointerCubeTexture texture){_environmentalMap = texture; };


    inline static PointerMaterial create(PointerTexture2D texture, PointerTexture2D normal = nullptr){
        return PointerMaterial(new Material(texture, normal));
    }
};




#endif //GRAPHICSPROJECT_MATERIAL_H
