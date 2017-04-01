//
// Created by gabriel on 24.9.2016.
//

#include "Maths.h"

glm::mat4 Maths::createTransformationMatrix(const float &posX, const float &posY, const float &posZ,
                                            const float &rotX, const float &rotY, const float &rotZ,
                                            const float &scaleX, const float &scaleY, const float &scaleZ){
    glm::vec3 translate = glm::vec3(posX, posY, posZ);
    glm::mat4 translateMatrix = glm::translate(translate);

    glm::mat4 rotationMatrix = glm::mat4(1.0f);
    rotationMatrix *= glm::rotate(rotX, glm::vec3(1, 0, 0));
    rotationMatrix *= glm::rotate(rotY, glm::vec3(0, 1, 0));
    rotationMatrix *= glm::rotate(rotZ, glm::vec3(0, 0, 1));

    glm::vec3 scale = glm::vec3(scaleX, scaleY, scaleZ);
    glm::mat4 scaleMatrix = glm::scale(scale);

    return translateMatrix * rotationMatrix * scaleMatrix;
}



glm::mat4 Maths::createViewMatrix(const float &pitch, const float &yaw, const float &roll, const float &x, const float &y, const float &z){
    glm::mat4 resultMatrix = glm::mat4(1.0f);
    if(NEQ(pitch, 0)){
        resultMatrix *= glm::rotate(pitch, glm::vec3(1, 0, 0));
    }
    if(NEQ(yaw, 0)){
        resultMatrix *= glm::rotate(yaw, glm::vec3(0, 1, 0));
    }
    if(NEQ(roll, 0)){
        resultMatrix *= glm::rotate(roll, glm::vec3(0, 0, 1));
    }
    resultMatrix *= glm::translate(glm::vec3(-x, -y, -z));
    return resultMatrix;
}


glm::mat4 Maths::createTransformationMatrix(const float &posX, const float &posY, const float &scaleX, const float &scaleY){
    glm::mat4 matrix = glm::mat4(1.0f);
    matrix *= glm::translate(glm::vec3(posX, posY, 0.0f));
    matrix *= glm::scale(glm::vec3(scaleX, scaleY, 1.0f));
    return matrix;
}

/*
glm::mat4 Maths::createTransformationMatrix(Transform * transform){
    return createTransformationMatrix(transform -> getPosX(), transform -> getPosY(), transform -> getPosZ(),
                                      transform -> getRotX(), transform -> getRotY(), transform -> getRotZ(),
                                      transform -> getScaleX(), transform -> getScaleY(), transform -> getScaleZ());
}
*/


glm::mat4 Maths::createTransformationMatrix(Vector2f pos, Vector2f scale) {
    return createTransformationMatrix(pos.x, pos.y, scale.x, scale.y);
}