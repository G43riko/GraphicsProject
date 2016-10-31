//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_MATERIAL_H
#define GRAPHICSPROJECT_MATERIAL_H

#include <memory>
#include "Texture2D.h"

class Material {
    private:
        PointerTexture2D diffuse = nullptr;
        PointerTexture2D normal = nullptr;
        PointerTexture2D specular = nullptr;
        PointerTexture2D alpha = nullptr;
    public:
        Material(PointerTexture2D);
        Material(PointerTexture2D, PointerTexture2D);
        PointerTexture2D getDiffuse(void);
        PointerTexture2D getNormal(void);
        PointerTexture2D getSpecular(void);
        PointerTexture2D getAlpha(void);
};
typedef std::shared_ptr<Material> PointerMaterial;
PointerMaterial createMaterial(PointerTexture2D);
PointerMaterial createMaterial(PointerTexture2D, PointerTexture2D);



#endif //GRAPHICSPROJECT_MATERIAL_H
