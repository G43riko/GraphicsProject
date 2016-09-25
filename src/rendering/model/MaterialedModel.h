//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_MATERIALEDMODEL_H
#define GRAPHICSPROJECT_MATERIALEDMODEL_H


#include "RawModel.h"
#include "../material/Material.h"

class MaterialedModel {
private:
    RawModel * model;
    Material * material;
public:
    MaterialedModel(RawModel *, Material *);

    RawModel * getModel(void);
    Material * getMaterial(void);
};


#endif //GRAPHICSPROJECT_MATERIALEDMODEL_H
