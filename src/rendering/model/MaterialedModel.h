//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_MATERIALEDMODEL_H
#define GRAPHICSPROJECT_MATERIALEDMODEL_H


#include "RawModel.cpp"
#include "../material/Material.cpp"

class MaterialedModel {
private:
    RawModel * model = NULL;
    Material * material = NULL;
public:
    MaterialedModel(RawModel * model, Material * material) {
        this -> model = model;
        this -> material = material;
    }

    RawModel * getModel(){
        return model;
    }

    Material * getMaterial(){
        return material;
    }
};


#endif //GRAPHICSPROJECT_MATERIALEDMODEL_H
