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
        void setEnvironmentalMap(PointerCubeTexture texture);
        PointerCubeTexture getEnvironmentalMap(void);
        float shineDumber = DEFAULT_MATERIAL_SHINE_DUMPER;
        float reflectivity = DEFAULT_MATERIAL_REFLECTIVITY;

        Material(PointerTexture2D diffuse);
        Material(PointerTexture2D diffuse, PointerTexture2D normal);

        PointerTexture2D getDiffuse(void);
        PointerTexture2D getSpecular(void);
        PointerTexture2D getNormal(void);
        PointerTexture2D getAlpha(void);
        PointerTexture2D getBump(void);

        bool hasEnvironmentalMap(void);
};
typedef std::shared_ptr<Material> PointerMaterial;
PointerMaterial createMaterial(PointerTexture2D diffuse);
PointerMaterial createMaterial(PointerTexture2D diffuse, PointerTexture2D normal);



#endif //GRAPHICSPROJECT_MATERIAL_H
