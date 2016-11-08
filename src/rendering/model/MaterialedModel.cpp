//
// Created by gabriel on 24.9.2016.
//

#include "MaterialedModel.h"

PointerMaterialedModel createMaterialedModel(std::string fileName, Loader loader){
    auto diffuse = ContentLoader::loadTexturePNG("res/textures/" + fileName + ".png");
    auto normal = ContentLoader::loadTexturePNG("res/textures/" + fileName + "Normal.png");
    auto rawModel = PointerRawModel(loader.loadToVao(ContentLoader::loadOBJ("res/models/" + fileName + ".obj")));
    return PointerMaterialedModel(new MaterialedModel(rawModel, createMaterial(diffuse, normal)));
}

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