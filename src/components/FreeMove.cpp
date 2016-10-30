//
// Created by gabriel on 29.10.2016.
//

#include "FreeMove.h"

void FreeMove::move(Vector3f direction, const float& amount){
    if(target){
        direction.normalize();
        direction *= amount;
        target->getTransform()->move(direction.x, direction.y, direction.z);
    }
}

void FreeMove::processInput(Input input, float delta){
    /*
    if(Input::isKeyDown(keyForward)) {
        //position -> z -= movSpeed;
        position -> x += static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
        position -> z += static_cast<float>(-cos(pitch) * cos(yaw) * movSpeed);
    }
    if(Input::isKeyDown(keyDown)) {
        //position->z += movSpeed;
        position -> x -= static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
        position -> z -= static_cast<float>(-cos(pitch) * cos(yaw) * movSpeed);
    }


    if(Input::isKeyDown(keyLeft)) {
        //position->x -= movSpeed;
        position -> z -= static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
        position -> x -= static_cast<float>(cos(pitch) * cos(yaw) * movSpeed);
    }
    if(Input::isKeyDown(keyRight)) {
        //position->x += movSpeed;
        position -> z += static_cast<float>(cos(pitch) * sin(yaw) * movSpeed);
        position -> x += static_cast<float>(cos(pitch) * cos(yaw) * movSpeed);
    }
    */
    if(Input::isKeyDown(keyDown))
        move(Vector3f(0, 1, 0), speed);

    if(Input::isKeyDown(keyUp))
        move(Vector3f(0, -1, 0), speed);

}

void FreeMove::setTarget(Entity & target){
    this -> target = &target;
}

FreeMove::FreeMove(float moveSpeed, int forwardKey, int backKey, int leftKey, int rightKey, int upKey, int downKey){
    keyForward = forwardKey;
    keyBack = forwardKey;
    keyLeft = forwardKey;
    keyRight = forwardKey;
    keyUp = forwardKey;
    keyDown = forwardKey;
    speed = moveSpeed;


}