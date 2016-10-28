//
// Created by gabriel on 24.9.2016.
//

#include "MaterialedModel.h"

PointerMaterialedModel createMaterialedModel(PointerRawModel model, PointerMaterial material){
    return PointerMaterialedModel(new MaterialedModel(model, material));
}

MaterialedModel::MaterialedModel(PointerRawModel model, PointerMaterial material) {
    this -> model = model;
    this -> material = material;
}


PointerRawModel MaterialedModel::getModel(void){
    return model;
}

PointerMaterial MaterialedModel::getMaterial(void){
    return material;
}