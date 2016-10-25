//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_MATERIAL_H
#define GRAPHICSPROJECT_MATERIAL_H

#include <memory>
#include "Texture2D.h"

class Material;
typedef std::shared_ptr<Material> PointerMaterial;
class Material {
    private:
        PointerTexture2D diffuse;
    public:
        static PointerMaterial create(PointerTexture2D texture){
            return PointerMaterial(new Material(texture));
        }
        Material(PointerTexture2D);
        PointerTexture2D getDiffuse(void);
};



#endif //GRAPHICSPROJECT_MATERIAL_H
