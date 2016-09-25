//
// Created by gabriel on 24.9.2016.
//

#include "MaterialedModel.h"

MaterialedModel::MaterialedModel(RawModel * model, Material * material) {
this -> model = model;
this -> material = material;
}

RawModel * MaterialedModel::getModel(void){
    return model;
}

Material * MaterialedModel::getMaterial(void){
    return material;
}