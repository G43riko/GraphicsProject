//
// Created by gabriel on 25.9.2016.
//

#include "Camera.h"
#include "../utils/Maths.h"

Vector3f * Camera::UP = new Vector3f(0, 1, 0);

Camera::Camera(void){
    projectionMatrix = glm::perspectiveFov<float>(FOV, static_cast<float>(WindowManager::width),
                                                  static_cast<float>(WindowManager::height), NEAR_PLANE, FAR_PLANE);
}
glm::mat4 Camera::getProjectionMatrix(void){
    return projectionMatrix;
}


void Camera::input(void){
    float movSpeed = 0.1f;
    float rotSpeed = 0.1f;

    if(Input::isKeyDown(Input::KEY_W))
        position -> z -= movSpeed;
    if(Input::isKeyDown(Input::KEY_S))
        position -> z += movSpeed;


    if(Input::isKeyDown(Input::KEY_A))
        position -> x -= movSpeed;
    if(Input::isKeyDown(Input::KEY_D))
        position -> x += movSpeed;

    if(Input::isKeyDown(Input::KEY_LSHIFT))
        position -> y -= movSpeed;
    if(Input::isKeyDown(Input::KEY_SPACE))
        position -> y += movSpeed;

    /*
    if(Input::isKeyDown(Input::KEY_Q))
        yaw -= rotSpeed;
    if(Input::isKeyDown(Input::KEY_E))
        yaw += rotSpeed;

    updateForward();
    */
}

glm::mat4 Camera::getViewMatrix(void){
    return Maths::createViewMatrix(this);
}