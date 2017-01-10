//
// Created by gabriel on 19.11.2016.
//

#ifndef GRAPHICSPROJECT_TOPVIEW_H
#define GRAPHICSPROJECT_TOPVIEW_H


#include <src/rendering/Camera.h>
#include <src/rendering/model/Entity.h>
#include <src/game/GameObject.h>
#include "BasicView.h"

class TopView : public BasicView{
private:
    Vector3f realPosition;
    float speed = 1;
    float velocityPower = 0.05f;
    float height;
public:
    TopView(PointerCamera camera, float height, GameObject * player = nullptr) : BasicView(camera, player, "topView"){
        this -> height = height;
        realPosition = camera -> position;
        camera -> position.y = height;
        camera -> pitch = (float)M_PI_2;
        player->getObject()->immortal = true;
    }

    void update(float delta){
        Vector3f position = realPosition;
        //float rotSpeed = 0.2;
        if(Input::isKeyDown(GLFW_KEY_W)) {
            position.z -= speed;
            realPosition.z -= speed;
            player -> getVelocity() -> z -= velocityPower * cosF(camera -> yaw);
            player -> getVelocity() -> x += velocityPower * sinF(camera -> yaw);
        }
        if(Input::isKeyDown(GLFW_KEY_S)) {
            position.z += speed;
            realPosition.z += speed;
            player -> getVelocity() -> z += velocityPower * cosF(camera -> yaw);
            player -> getVelocity() -> x -= velocityPower * sinF(camera -> yaw);
        }

        if(Input::isKeyDown(GLFW_KEY_A)) {
            position.x -= speed;
            realPosition.x -= speed;
            player -> getVelocity() -> x -= velocityPower * cosF(camera -> yaw);
            player -> getVelocity() -> z -= velocityPower * sinF(camera -> yaw);
        }
        if(Input::isKeyDown(GLFW_KEY_D)) {
            position.x += speed;
            realPosition.x += speed;
            player -> getVelocity() -> x += velocityPower * cosF(camera -> yaw);
            player -> getVelocity() -> z += velocityPower * sinF(camera -> yaw);
        }

        if(Input::isKeyDown(GLFW_KEY_LEFT)) {
            camera -> yaw += 0.1f;
        }

        if(Input::isKeyDown(GLFW_KEY_UP)) {
            camera -> pitch += 0.1f;
        }

        if(Input::isKeyDown(GLFW_KEY_RIGHT)) {
            camera -> yaw -= 0.1f;
        }

        if(Input::isKeyDown(GLFW_KEY_DOWN)) {
            camera -> pitch -= 0.1f;
        }
        camera -> pitch = clamp(camera -> pitch , 0.07f, 1.54f);
        Vector3f * playerPos = player -> getObject() -> getTransform() ->getPosition();
        float tmpHeight = height - Input::getMouseScroll().y;
        if(tmpHeight < 3)
            tmpHeight = 3;
        position.y = playerPos -> y + tmpHeight * sinF(camera -> pitch);
        position.z = playerPos -> z + tmpHeight * cosF(-camera -> yaw) * cosF(camera -> pitch);
        position.x = playerPos -> x + tmpHeight * sinF(-camera -> yaw) * cosF(camera -> pitch);
        camera -> position = position;
    }
};


#endif //GRAPHICSPROJECT_TOPVIEW_H
