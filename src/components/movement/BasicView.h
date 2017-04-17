//
// Created by gabriel on 13.12.2016.
//

#ifndef GRAPHICSPROJECT_BASICVIEW_H
#define GRAPHICSPROJECT_BASICVIEW_H

class BasicView{
protected:
    PointerCamera camera = nullptr;
    GameObject * player = nullptr;
public:
    virtual ~BasicView(){};
    const std::string name;
    BasicView(PointerCamera camera, GameObject * player, std::string name) : name(name){
        this -> camera = camera;
        this -> player = player;
    }
    virtual void cleanUp(void){};
    virtual void update(float delta){};
};

#endif //GRAPHICSPROJECT_BASICVIEW_H
