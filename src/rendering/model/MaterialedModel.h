//
// Created by gabriel on 24.9.2016.
//

#ifndef GRAPHICSPROJECT_MATERIALEDMODEL_H
#define GRAPHICSPROJECT_MATERIALEDMODEL_H

#include "RawModel.h"
#include <src/rendering/material/TextureManager.h>
#include "../material/Material.h"
#include "../../utils/Loader.h"

class MaterialedModel {
    const RawModel _model;
    const PointerMaterial _material = nullptr;

    MaterialedModel(const RawModel& model, PointerMaterial material) :
            _model(model),
            _material(material){}
public:
    inline const RawModel getModel(void) const{return _model;}
    inline PointerMaterial getMaterial(void) const{return _material;}

    inline static PointerMaterialedModel create(std::string fileName, Loader loader){
        auto diffuse = TextureManager::instance.createTexture2D(TEXTURES_FOLDER + fileName + TEXTURES_EXTENSION);
        auto rawModel = PointerRawModel(loader.loadToVao(ContentLoader::loadOBJ(MODELS_FOLDER + fileName + MODELS_EXTENSION)));
        return PointerMaterialedModel(new MaterialedModel(*rawModel, Material::create(diffuse/*, normal*/)));
    }

    inline static PointerMaterialedModel create(PointerRawModel model, PointerMaterial material){
        return PointerMaterialedModel(new MaterialedModel(*model, material));
    }
};

#endif //GRAPHICSPROJECT_MATERIALEDMODEL_H
