//
// Created by gabriel on 19.11.2016.
//

#ifndef GRAPHICSPROJECT_FPSVIEW_H
#define GRAPHICSPROJECT_FPSVIEW_H


#include <src/rendering/Camera.h>
#include <src/game/Ball.h>
#include "BasicView.h"

//#define FORWARD GLFW_KEY_W
//#define BACK GLFW_KEY_S
//#define LEFT GLFW_KEY_A
//#define RIGHT GLFW_KEY_D

class FpsView : public BasicView{
private:
    bool mouseLocked = false;
    Vector2f center = center;
    const float velocityPower = 0.05f;
    const float yOffset = 1.0f;
    bool rotate = false;
    bool move = false;
    bool flyMode = true;
    inline void checkMoveKeys(float delta){
        /*	MOVING KEYS
         * 	W, A, S, D
         */

        if(Input::isKeyDown(GLFW_KEY_W)){
            camera -> getTransform() -> move(camera -> getForwardVector() * getMoveSpeed() * delta);
        }
        if(Input::isKeyDown(GLFW_KEY_S)){
            camera -> getTransform() -> move(camera -> getForwardVector() * getMoveSpeed() * -delta);
        }
        if(Input::isKeyDown(GLFW_KEY_D)){
            camera -> getTransform() -> move(camera -> getRightVector() * getMoveSpeed() * delta);
        }
        if(Input::isKeyDown(GLFW_KEY_A)){
            camera -> getTransform() -> move(camera -> getRightVector() * getMoveSpeed() * -delta);
        }
    }

    inline void checkRotateAndFlyKeys(float delta){
        /*	ROTATION
         * 	Q and E
         */

        if(Input::isKeyDown(GLFW_KEY_Q)){
            camera -> getTransform() -> getRotation().rotate(Vector3f(0.0f, getRotSpeed() * delta, 0.0f));
            rotate = true;
        }

        if(Input::isKeyDown(GLFW_KEY_E)){
            camera -> getTransform() -> getRotation().rotate(Vector3f(0.0f, getRotSpeed() * -delta, 0.0f));
            rotate = true;
        }

        /*	FLYING KEYS
         * 	SHIFT, SPACER
         */

        if(flyMode){
            if(Input::isKeyDown(GLFW_KEY_SPACE)){
                camera ->getTransform()->move(0, getMoveSpeed(), 0);
                move = true;
            }

            if(Input::isKeyDown(GLFW_KEY_LEFT_SHIFT)){
                camera ->getTransform()->move(0, -getMoveSpeed(), 0);
                move = true;
            }
        }
    }

    inline bool mouseMove(float delta) {
        Vector2f deltaPos = Input::getMousePosition() - center;

        bool rotY = NEZ(deltaPos.x);
        bool rotX = NEZ(deltaPos.x);

        if (rotY) {
            camera->getTransform()->rotate(Vector3f(0, 1, 0), TO_RADIANS(-deltaPos.x * getRotSpeed()));
        }
        if (rotX) {
            camera->getTransform()->rotate(camera->getTransform()->getRotation().getRight(), TO_RADIANS(-deltaPos.y * getRotSpeed()));
        }

        if (rotY || rotX) {
            center = Input::getMousePosition();
            return true;
        }

        return false;
    }
public:
    inline FpsView(PointerCamera camera, bool flyMode = false, GameObject * player = nullptr) : BasicView(camera, player, "fpsView"){
        center = Input::getMousePosition();
    }

    inline void update(float delta){
        if(Input::getKeyDown(GLFW_KEY_P)) {
            mouseLocked = !mouseLocked;
            if(mouseLocked){
                Input::setMousePos(Input::getWindowCenter());
            }
            glfwSetInputMode(WindowManager::window, GLFW_CURSOR, mouseLocked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        }
        if(mouseLocked){
            checkMoveKeys(delta);
            checkRotateAndFlyKeys(delta);
            mouseMove(delta);
        }
    }
};


#endif //GRAPHICSPROJECT_FPSVIEW_H
