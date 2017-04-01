//
// Created by gabriel on 24.9.2016.
//

#include <src/rendering/material/TextureManager.h>
#include "MaterialedModel.h"

PointerMaterialedModel createMaterialedModel(std::string fileName, Loader loader){
    auto diffuse = TextureManager::createTexture2D(TEXTURES_FOLDER + fileName + TEXTURES_EXTENSION);
//    auto normal = TextureManager::createTexture2D("res/textures/" + fileName + "Normal.png");
    auto rawModel = PointerRawModel(loader.loadToVao(ContentLoader::loadOBJ(MODELS_FOLDER + fileName + MODELS_EXTENSION)));
    return PointerMaterialedModel(new MaterialedModel(rawModel, createMaterial(diffuse/*, normal*/)));
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