//
// Created by gabriel on 22.1.2017.
//

#ifndef GRAPHICSPROJECT_GAMEOBJECT_H
#define GRAPHICSPROJECT_GAMEOBJECT_H


#include <vector>
#include <src/utils/Transform.h>
#include "GameComponent.h"


class GameObject {
private:
    std::vector<GameComponent *> compoentns;
    std::vector<GameObject *> childrens;
    Transform transform = Transform();

    void update(float delta){
        for(auto component : compoentns){
            component -> update(delta);
        }
    };

    void input(void) {
        for (auto component : compoentns) {
            component->input();
        }
    };
public:
    Transform * getTransform(void) {return &transform;}

    void updateAll(float delta){
        update(delta);
        for(auto children : childrens){
            children -> updateAll(delta);
        }
    };

    void inputAll(void){
        input();
        for(auto children : childrens){
            children -> inputAll();
        }
    };

    GameObject * addChildren(GameObject * children){
        childrens.push_back(children);
        children -> getTransform()->setParent(&transform);
        return this;
    };
    GameObject * addComponent(GameComponent * component){
        component -> setParent(this);
        compoentns.push_back(component);
        return this;
    };
};


#endif //GRAPHICSPROJECT_GAMEOBJECT_H
