//
// Created by gabriel on 19.11.2016.
//

#ifndef GRAPHICSPROJECT_TOPVIEW_H
#define GRAPHICSPROJECT_TOPVIEW_H


#include <src/rendering/Camera.h>
#include <src/rendering/model/Entity.h>
#include <src/game/GameObject.h>

class TopView {
private:
    PointerCamera camera;
    Vector3f realPosition;
    float speed = 1;
    float velocityPower = 0.25f;
    float height;
    GameObject * player;
public:
    TopView(PointerCamera camera, float height, GameObject * player = nullptr){
        this -> camera = camera;
        this -> player = player;
        this -> height = height;
        realPosition = camera -> position;
        camera -> position.y = height;
        camera -> pitch = M_PI_2;
    }

    void input(){
        Vector3f position = realPosition;
        float rotSpeed = 0.2;
        if(Input::isKeyDown(GLFW_KEY_W)) {
            position.z -= speed;
            realPosition.z -= speed;
            player -> getVelocity() -> z -= velocityPower * cos(camera -> yaw);
            player -> getVelocity() -> x += velocityPower * sin(camera -> yaw);
        }
        if(Input::isKeyDown(GLFW_KEY_S)) {
            position.z += speed;
            realPosition.z += speed;
            player -> getVelocity() -> z += velocityPower * cos(camera -> yaw);
            player -> getVelocity() -> x -= velocityPower * sin(camera -> yaw);
        }

        if(Input::isKeyDown(GLFW_KEY_A)) {
            position.x -= speed;
            realPosition.x -= speed;
            player -> getVelocity() -> x -= velocityPower * cos(camera -> yaw);
            player -> getVelocity() -> z -= velocityPower * sin(camera -> yaw);
        }
        if(Input::isKeyDown(GLFW_KEY_D)) {
            position.x += speed;
            realPosition.x += speed;
            player -> getVelocity() -> x += velocityPower * cos(camera -> yaw);
            player -> getVelocity() -> z += velocityPower * sin(camera -> yaw);
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
        Vector3f * playerPos = player -> getObject() -> getTransform() ->getPosition();
        float tmpHeight = height - Input::getMouseScroll().y;
        position.y = playerPos -> y + tmpHeight * sin(camera -> pitch);
        position.z = playerPos -> z + tmpHeight * cos(-camera -> yaw) * cos(camera -> pitch);
        position.x = playerPos -> x + tmpHeight * sin(-camera -> yaw) * cos(camera -> pitch);
        camera -> position = position;
    }
};


#endif //GRAPHICSPROJECT_TOPVIEW_H
