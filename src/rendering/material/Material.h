//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_MATERIAL_H
#define GRAPHICSPROJECT_MATERIAL_H

#include <memory>
#include "Texture2D.h"
#include "CubeTexture.h"

class Material {
    PointerCubeTexture environmentalMap = nullptr;
    PointerTexture2D diffuse            = nullptr;
    PointerTexture2D specular           = nullptr;
    PointerTexture2D normal             = nullptr;
    PointerTexture2D alpha              = nullptr;
    PointerTexture2D bump               = nullptr;

    float shineDumber = DEFAULT_MATERIAL_SHINE_DUMPER;
    float reflectivity = DEFAULT_MATERIAL_REFLECTIVITY;
    inline Material(PointerTexture2D diffuse, PointerTexture2D normal = nullptr) : diffuse(diffuse), normal(normal){};
public:


    inline PointerTexture2D getSpecular(void) const{return specular;};
    inline PointerTexture2D getDiffuse(void) const{return diffuse;};
    inline PointerTexture2D getNormal(void) const{return normal;};
    inline PointerTexture2D getAlpha(void) const{return alpha;};
    inline PointerTexture2D getBump(void) const{return bump;};

    inline void setEnvironmentalMap(PointerCubeTexture texture){environmentalMap = texture; };
    inline PointerCubeTexture getEnvironmentalMap(void) const{return environmentalMap; };
    inline bool hasEnvironmentalMap(void) const{return environmentalMap == nullptr; };
    inline float getReflectivity(void) const{return reflectivity; };
    inline float getShineDumper(void) const{return shineDumber; };

    inline static PointerMaterial create(PointerTexture2D texture, PointerTexture2D normal = nullptr){
        return PointerMaterial(new Material(texture, normal));
    }
};




#endif //GRAPHICSPROJECT_MATERIAL_H
