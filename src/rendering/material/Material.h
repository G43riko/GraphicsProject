//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_MATERIAL_H
#define GRAPHICSPROJECT_MATERIAL_H

#include "Texture2D.h"


class Material {
    private:
        Texture2D * diffuse;
    public:
        Material(Texture2D *);
        Texture2D * getDiffuse(void);
};


#endif //GRAPHICSPROJECT_MATERIAL_H
