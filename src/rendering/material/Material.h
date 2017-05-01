//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_MATERIAL_H
#define GRAPHICSPROJECT_MATERIAL_H

#include <memory>
#include "Texture2D.h"
#include "CubeTexture.h"

class Material {
    private:
        PointerCubeTexture environmentalMap = nullptr;
        PointerTexture2D diffuse            = nullptr;
        PointerTexture2D specular           = nullptr;
        PointerTexture2D normal             = nullptr;
        PointerTexture2D alpha              = nullptr;
        PointerTexture2D bump               = nullptr;
    public:
        float shineDumber = DEFAULT_MATERIAL_SHINE_DUMPER;
        float reflectivity = DEFAULT_MATERIAL_REFLECTIVITY;

        inline Material(PointerTexture2D diffuse) : diffuse(diffuse){};
        inline Material(PointerTexture2D diffuse, PointerTexture2D normal) : diffuse(diffuse), normal(normal){};

        inline PointerTexture2D getSpecular(void) const{return specular;};
        inline PointerTexture2D getDiffuse(void) const{return diffuse;};
        inline PointerTexture2D getNormal(void) const{return normal;};
        inline PointerTexture2D getAlpha(void) const{return alpha;};
        inline PointerTexture2D getBump(void) const{return bump;};

        inline void setEnvironmentalMap(PointerCubeTexture texture){environmentalMap = texture; };
        inline PointerCubeTexture getEnvironmentalMap(void) const{return environmentalMap; };
        inline bool hasEnvironmentalMap(void) const{return environmentalMap == nullptr; };
};

typedef std::shared_ptr<Material> PointerMaterial;

inline PointerMaterial createMaterial(PointerTexture2D texture){
    return PointerMaterial(new Material(texture));
}
inline PointerMaterial createMaterial(PointerTexture2D texture, PointerTexture2D normal){
    return PointerMaterial(new Material(texture, normal));
}

#endif //GRAPHICSPROJECT_MATERIAL_H
