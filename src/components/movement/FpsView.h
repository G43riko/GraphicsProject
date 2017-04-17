//
// Created by gabriel on 19.11.2016.
//

#ifndef GRAPHICSPROJECT_FPSVIEW_H
#define GRAPHICSPROJECT_FPSVIEW_H


#include <src/rendering/Camera.h>
#include <src/game/Ball.h>
#include "BasicView.h"

class FpsView : public BasicView{
private:
    bool mouseLocked = false;
    Vector2f center = center;
    float velocityPower = 0.05f;
    const float yOffset = 1.0f;
public:
    FpsView(PointerCamera camera, bool flyMode = false, GameObject * player = nullptr) : BasicView(camera, player, "fpsView"){
        center = Input::getMousePosition();
    }

    void update(float delta){
        float movSpeed = 0.1f * delta;
        float rotSpeed = 0.05f * delta;
        float SENSITIVITY = 0.002f * delta;
        float yaw = camera -> yaw;
        float pitch = camera -> pitch;
        Vector3f position = camera -> position;

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
        camera -> position = position;

//        camera -> updateForward();
    }
};


#endif //GRAPHICSPROJECT_FPSVIEW_H
