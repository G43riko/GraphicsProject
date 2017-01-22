//
// Created by gabriel on 22.1.2017.
//

#ifndef GRAPHICSPROJECT_GAMECOMPONENT_H
#define GRAPHICSPROJECT_GAMECOMPONENT_H

class GameObject;

class GameComponent {
private:
    GameObject * parent = nullptr;

public:
    virtual void setParent(GameObject * parent){this -> parent = parent;}
    virtual void input(void){};
    virtual void update(float delta){};
};


#endif //GRAPHICSPROJECT_GAMECOMPONENT_H
