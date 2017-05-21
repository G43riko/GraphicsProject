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

    inline Matrix4f getViewMatrix(void){
        return Matrix4f::initTranslation(transform.getPosition().getInverted()) * transform.getRotation().toRotationMatrix();
    }

    inline Vector3f& getPosition(void){
        return transform.getPosition();
    }
    inline void cleanUp(void){
        CHECK_AND_DEL(picker);
    }
    inline const Vector3f& getMouseDirection(void) const{
        if(IS_NULL(picker)){
            throw getMessage(Messages::UNINITIALIZED_MOUSE_PICKER);
        }
        return picker -> getCurrentRay();
    }
};

#endif //GRAPHICSPROJECT_BASICCAMERA_H
