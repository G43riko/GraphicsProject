//
// Created by gabriel on 29.10.2016.
//

#ifndef GRAPHICSPROJECT_FREEMOVE_H
#define GRAPHICSPROJECT_FREEMOVE_H


#include <src/rendering/model/Entity.h>
#include <src/utils/Input.h>

class FreeMove {
    private:
        Entity * target = nullptr;
        int keyForward;
        int keyBack;
        int keyLeft;
        int keyRight;
        int keyUp;
        int keyDown;
        float speed;
        void move(Vector3f, const float&);
    public:
        FreeMove(float, int = Input::KEY_W, int = Input::KEY_S, int = Input::KEY_A, int = Input::KEY_D, int = Input::KEY_SPACE, int = Input::KEY_LSHIFT);
        void setTarget(Entity &);
        void processInput(Input, float);
};

#endif //GRAPHICSPROJECT_FREEMOVE_H
