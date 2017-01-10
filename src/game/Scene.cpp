//
// Created by gabriel on 16.10.2016.
//

#include "Scene.h"

Scene::Scene(Loader loader, CubeTexture sky) : sky(sky){
    sphereModel = PointerRawModel(loader.loadToVao(ContentLoader::loadOBJ("res/models/sphere.obj")));
}