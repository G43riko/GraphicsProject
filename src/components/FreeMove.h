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
        FreeMove(float, int = GLFW_KEY_W, int = GLFW_KEY_S, int = GLFW_KEY_A, int = GLFW_KEY_D, int = GLFW_KEY_SPACE, int = GLFW_KEY_LEFT_SHIFT);
        void setTarget(Entity &);
        void processInput(Input, float);
};

#endif //GRAPHICSPROJECT_FREEMOVE_H
