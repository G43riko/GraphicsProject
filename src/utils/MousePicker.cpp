//
// Created by gabriel on 1.4.2017.
//

#include "MousePicker.h"
#include <src/core/BasicCamera.h>

void MousePicker::update(void){
    throw "ULOHA 1";
//    viewMatrix = glm::rotate(-camera -> pitch, glm::vec3(1, 0, 0));
//    viewMatrix *= glm::rotate(-camera -> yaw, glm::vec3(0, 1, 0));
    viewMatrix *= glm::translate(glm::vec3(-camera -> getPosition().x, -camera -> getPosition().y, -camera -> getPosition().z));
    currentRay = calculateMouseRay();
}

MousePicker::MousePicker(BasicCamera * camera) {
    this -> projectionMatrix = camera -> getProjectionMatrix();
    this -> camera = camera;
    //		this.viewMatrix = Maths.MatrixToGMatrix(Maths.createViewMatrix(camera.getPosition(), camera.getPitch(), camera.getYaw()));

}