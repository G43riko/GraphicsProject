//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_MATERIAL_H
#define GRAPHICSPROJECT_MATERIAL_H

#include <memory>
#include "Texture2D.h"


class Material {
    private:
    PointerTexture2D diffuse;
    public:
        Material(PointerTexture2D);
        PointerTexture2D getDiffuse(void);
};
typedef std::shared_ptr<Material> PointerMaterial;



#endif //GRAPHICSPROJECT_MATERIAL_H
