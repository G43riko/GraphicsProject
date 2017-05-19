//
// Created by gabriel on 14.1.2017.
//

#ifndef GRAPHICSPROJECT_BASICCAMERA_H
#define GRAPHICSPROJECT_BASICCAMERA_H

#include <src/Messages.h>
#include <src/utils/Transform.h>
#include <src/utils/MousePicker.h>

class BasicCamera{
protected:
    glm::mat4 projectionMatrix;//TODO prerobiť na GMatrix
    MousePicker * picker    = nullptr;
    Transform transform     = Transform();
public:
    inline glm::mat4 getProjectionMatrix(void) const{return projectionMatrix; }
    inline Vector3f getForward(void){return transform.getRotation().getBack(); }

    inline glm::mat4 getViewMatrix(void){
        Vector3f pos = transform.getPosition();
        //TODO prerobiť iba na GMatrix
        return Matrix4f::toGlmMatrix(transform.getRotation().toRotationMatrix()) * glm::translate(glm::vec3(-pos.x, -pos.y, -pos.z));
    }
    inline Vector3f& getPosition(void){
        return transform.getPosition();
    }
    inline void cleanUp(void){
        CHECK_AND_DEL(picker);
    }
    inline Vector3f getMouseDirection(void){
        if(IS_NULL(picker)){
            throw getMessage(Messages::UNINITIALIZED_MOUSE_PICKER);
        }
        return picker -> getCurrentRay();
    }
};

#endif //GRAPHICSPROJECT_BASICCAMERA_H
