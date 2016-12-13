//
// Created by gabriel on 13.12.2016.
//

#ifndef GRAPHICSPROJECT_BASICVIEW_H
#define GRAPHICSPROJECT_BASICVIEW_H

#include <src/rendering/Camera.h>
#include <src/game/GameObject.h>

class BasicView{
protected:
    PointerCamera camera = nullptr;
    GameObject * player = nullptr;

public:
    const std::string name;
    BasicView(PointerCamera camera, GameObject * player, std::string name) : name(name){
        this -> camera = camera;
        this -> player = player;
    }
    virtual void input(void){};
};

#endif //GRAPHICSPROJECT_BASICVIEW_H
