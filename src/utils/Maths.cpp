//
// Created by gabriel on 24.9.2016.
//

#include "Maths.h"

glm::mat4 Maths::createTransformationMatrix(Transform * transform){
    glm::vec3 translate = glm::vec3(transform -> getPosX(), transform -> getPosY(), transform -> getPosZ());
    glm::mat4 translateMatrix = glm::translate(translate);

    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix *= glm::rotate(transform -> getRotX(), glm::vec3(1, 0, 0));
    rotationMatrix *= glm::rotate(transform -> getRotY(), glm::vec3(0, 1, 0));
    rotationMatrix *= glm::rotate(transform -> getRotZ(), glm::vec3(0, 0, 1));

    glm::vec3 scale = glm::vec3(transform -> getScaleX(), transform -> getScaleY(), transform -> getScaleZ());
    glm::mat4 scaleMatrix = glm::scale(scale);

    return translateMatrix * rotationMatrix * scaleMatrix;
}

glm::mat4 Maths::createViewMatrix(Camera * camera){
    glm::mat4 resultMatrix = glm::mat4(1.0f);
    resultMatrix *= glm::rotate(camera -> pitch, glm::vec3(1, 0, 0));
    resultMatrix *= glm::rotate(camera -> yaw, glm::vec3(0, 1, 0));
    //resultMatrix *= glm::vec4(-camera -> position -> x, -camera -> position -> y, -camera -> position -> z, 1);
    resultMatrix *= glm::translate(glm::vec3(-camera -> position -> x, -camera -> position -> y, -camera -> position -> z));
    return resultMatrix;
}

glm::mat4 Maths::createTransformationMatrix(Vector2f * pos, Vector2f * scale) {
    glm::mat4 matrix = glm::mat4(1.0f);
    matrix *= glm::translate(glm::vec3(pos -> x, pos -> y, 0.0f));
    matrix *= glm::scale(glm::vec3(scale -> x, scale -> y, 1.0f));
    return matrix;
}