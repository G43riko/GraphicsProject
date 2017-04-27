//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_MATERIALEDMODEL_H
#define GRAPHICSPROJECT_MATERIALEDMODEL_H

#include "RawModel.h"
#include <src/rendering/material/TextureManager.h>
#include "../material/Material.h"
#include "../../utils/FileLoader.h"
#include "../../utils/Loader.h"

class MaterialedModel {
private:
    PointerRawModel model     = nullptr;
    PointerMaterial material  = nullptr;
public:
    inline MaterialedModel(PointerRawModel model, PointerMaterial material) : model(model), material(material){};

    inline PointerRawModel getModel(void) const{return model;}
    inline PointerMaterial getMaterial(void) const{return material;}
};
typedef std::shared_ptr<MaterialedModel> PointerMaterialedModel;

inline PointerMaterialedModel createMaterialedModel(std::string fileName, Loader loader){
    auto diffuse = TextureManager::createTexture2D(TEXTURES_FOLDER + fileName + TEXTURES_EXTENSION);
    auto rawModel = PointerRawModel(loader.loadToVao(ContentLoader::loadOBJ(MODELS_FOLDER + fileName + MODELS_EXTENSION)));
    return PointerMaterialedModel(new MaterialedModel(rawModel, createMaterial(diffuse/*, normal*/)));
}

inline PointerMaterialedModel createMaterialedModel(PointerRawModel model, PointerMaterial material){
    return PointerMaterialedModel(new MaterialedModel(model, material));
}
#endif //GRAPHICSPROJECT_MATERIALEDMODEL_H
