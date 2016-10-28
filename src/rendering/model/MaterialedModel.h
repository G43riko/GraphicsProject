//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_MATERIALEDMODEL_H
#define GRAPHICSPROJECT_MATERIALEDMODEL_H

#include "RawModel.h"
#include "../material/Material.h"

class MaterialedModel {
private:
    PointerRawModel model;
    PointerMaterial material;
public:
    MaterialedModel(PointerRawModel, PointerMaterial);

    PointerRawModel getModel(void);
    PointerMaterial getMaterial(void);
};
typedef std::shared_ptr<MaterialedModel> PointerMaterialedModel;
PointerMaterialedModel createMaterialedModel(PointerRawModel, PointerMaterial);


#endif //GRAPHICSPROJECT_MATERIALEDMODEL_H
