//
// Created by gabriel on 16.10.2016.
//

#ifndef GRAPHICSPROJECT_SCENE_H
#define GRAPHICSPROJECT_SCENE_H


#include <src/rendering/model/Entity.h>
#include "Light.h"
#include <map>
#include <src/rendering/Renderer.h>

class Scene {
private:
    std::map<int, PointerEntity> entities;
    std::map<int, PointerLight> lights;
public:
    void addLight(PointerLight light){
        lights[light -> getId()] = light;
    }
    void addEntity(PointerEntity entity){
        entities[entity -> getId()] = entity;
    }

    void render(Renderer renderer){

    }

};


#endif //GRAPHICSPROJECT_SCENE_H
