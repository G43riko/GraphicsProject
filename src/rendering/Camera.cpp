//
// Created by gabriel on 25.9.2016.
//

#include "Camera.h"
#include <sys/time.h>

Camera::Camera(void){
    projectionMatrix = glm::perspectiveFov<float>(FOV,
                                                  static_cast<float>(WindowManager::width),
                                                  static_cast<float>(WindowManager::height),
                                                  NEAR_PLANE,
                                                  FAR_PLANE);
}
glm::mat4 Camera::getProjectionMatrix(void){
    return projectionMatrix;
}

float toRadians(float val){
    return static_cast<float>(val * (M_PI / 180));
}


bool isNotZero(float val){
    return val > 0 || val < 0;
}

glm::mat4 Camera::getViewMatrix(void){
    return Maths::createViewMatrix(pitch, yaw, roll, position.x, position.y, position.z);
}