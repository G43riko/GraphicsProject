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
    picker = new MousePicker(this);
}
Vector3f Camera::getForward(void){
    return transform.getRotation()->getBack();
}
glm::mat4 Camera::getProjectionMatrix(void){
    return projectionMatrix;
}
void Camera::cleanUp(void){
    delete picker;
}
glm::mat4 Camera::getViewMatrix(void){
//    return Maths::createViewMatrix(pitch, yaw, roll, position.x, position.y, position.z);
    Vector3f pos = transform.getPosition();
    return Matrix4f::toGlmMatrix(transform .getRotation() -> toRotationMatrix()) * glm::translate(glm::vec3(-pos.x, -pos.y, -pos.z));
}