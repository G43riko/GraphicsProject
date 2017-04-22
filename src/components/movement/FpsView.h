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
    float velocityPower = 0.05f;
    const float yOffset = 1.0f;
    bool rotate = false;
    bool move = false;
    bool flyMode = true;

    float getMoveSpeed(void){
        return 1;
    }
    float getRotSpeed(void){
        return 0.05;
    }
    void checkMoveKeys(float delta){
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

    void checkRotateAndFlyKeys(float delta){
        /*	ROTATION
         * 	Q and E
         */

        if(Input::isKeyDown(GLFW_KEY_Q)){
            camera -> getTransform() -> getRotation()->rotate(Vector3f(0.0f, getRotSpeed() * delta, 0.0f));
            rotate = true;
        }

        if(Input::isKeyDown(GLFW_KEY_E)){
            camera -> getTransform() -> getRotation() -> rotate(Vector3f(0.0f, getRotSpeed() * -delta, 0.0f));
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

    bool mouseMove(float delta) {
        Vector2f deltaPos = Input::getMousePosition() - center;

        bool rotY = deltaPos.x != 0;
        bool rotX = deltaPos.x != 0;

        if (rotY) {
            camera->getTransform()->rotate(Vector3f(0, 1, 0), TO_RADIANS(-deltaPos.x * getRotSpeed()));
        }
        if (rotX) {
            camera->getTransform()->rotate(camera->getTransform()->getRotation()->getRight(), TO_RADIANS(-deltaPos.y * getRotSpeed()));
        }

        if (rotY || rotX) {
            center = Input::getMousePosition();
            return true;
        }

        return false;
    }
public:
    FpsView(PointerCamera camera, bool flyMode = false, GameObject * player = nullptr) : BasicView(camera, player, "fpsView"){
        center = Input::getMousePosition();
    }

    void update(float delta){
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

    void update2(float delta){
        float movSpeed = 0.1f * delta;
        float rotSpeed = 0.05f * delta;
        float SENSITIVITY = 0.002f * delta;
        float yaw = camera -> yaw;
        float pitch = camera -> pitch;
        Vector3f position = camera -> getPosition();

        if(mouseLocked) {
            Vector2f deltaPos = Input::getMousePosition() - center;
            bool rotY = NEZ(deltaPos.x);
            bool rotX = NEZ(deltaPos.y);

            if(rotY){
                pitch += deltaPos.y * SENSITIVITY;
            }

            if(rotX){
                yaw += deltaPos.x * SENSITIVITY;
            }

            if(rotY || rotX)
                center = Input::getMousePosition();
        }

        if(Input::getKeyDown(GLFW_KEY_P)) {
            mouseLocked = !mouseLocked;
            if(mouseLocked)
                Input::setMousePos(Input::getWindowCenter());
            glfwSetInputMode(WindowManager::window, GLFW_CURSOR, mouseLocked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
        }


        if(Input::isKeyDown(GLFW_KEY_W)) {
            //position -> z -= movSpeed;
            if(player){
                player -> getVelocity() -> z -= velocityPower * COSF(camera -> yaw);
                player -> getVelocity() -> x += velocityPower * SINF(camera -> yaw);
            }
            else{
                position.x += static_cast<float>(cos(camera -> pitch) * sin(yaw) * movSpeed);
                position.z += static_cast<float>(-cos(camera -> pitch) * cos(yaw) * movSpeed);
            }
        }
        if(Input::isKeyDown(GLFW_KEY_S)) {
            //position->z += movSpeed;
            if(player){
                player -> getVelocity() -> z += velocityPower * COSF(camera -> yaw);
                player -> getVelocity() -> x -= velocityPower * SINF(camera -> yaw);
            }
            else{
                position.x -= static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
                position.z -= static_cast<float>(-cos(pitch) * cos(yaw) * movSpeed);
            }
        }

        if(Input::isKeyDown(GLFW_KEY_A)) {
            //position->x -= movSpeed;

            if(player){
                player -> getVelocity() -> x -= velocityPower * COSF(camera -> yaw);
                player -> getVelocity() -> z -= velocityPower * SINF(camera -> yaw);
            }
            else{
                position.z -= static_cast<float>(cos(pitch) * SINF(yaw) * movSpeed);
                position.x -= static_cast<float>(cos(pitch) * COSF(yaw) * movSpeed);
            }
        }
        if(Input::isKeyDown(GLFW_KEY_D)) {
            //position->x += movSpeed;

            if(player){
                player -> getVelocity() -> x += velocityPower * COSF(camera -> yaw);
                player -> getVelocity() -> z += velocityPower * SINF(camera -> yaw);
            }
            else{
                position.z += static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
                position.x += static_cast<float>(cos(pitch) * cos(yaw) * movSpeed);
            }
        }

        if(player){
            position = player->getObject()->getTransform()->getPosition();
            position.y += yOffset;
        }
        else{
            if(Input::isKeyDown(GLFW_KEY_LEFT_SHIFT ))
                position.y -= movSpeed;
            if(Input::isKeyDown(GLFW_KEY_SPACE))
                position.y += movSpeed;
        }
        if(Input::isKeyDown(GLFW_KEY_Q)){
            yaw -= rotSpeed;
        }
        if(Input::isKeyDown(GLFW_KEY_E)){
            yaw += rotSpeed;
        }
        if(Input::isKeyDown(GLFW_KEY_U)){
            pitch -= rotSpeed;
        }
        if(Input::isKeyDown(GLFW_KEY_J)){
            pitch += rotSpeed;
        }


        camera -> yaw = yaw;
        camera -> pitch = pitch;
        camera ->getTransform()->setPosition(position);
//        camera -> setPosition(position);

//        camera -> updateForward();
    }
};


#endif //GRAPHICSPROJECT_FPSVIEW_H
