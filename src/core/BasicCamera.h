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
    Matrix4f projectionMatrix;//TODO prerobiť na GMatrix
    MousePicker * picker    = nullptr;
    Transform transform     = Transform();
public:
    //TODO: tieto veci su editovatelne
    const float FOV           = DEFAULT_CAMERA_FOV;
    const float FAR_PLANE     = DEFAULT_CAMERA_FAR_PLANE;
    const float NEAR_PLANE    = DEFAULT_CAMERA_NEAR_PLANE;

    inline const Matrix4f& getProjectionMatrix(void) const{return projectionMatrix; }
    inline Vector3f getForward(void) {return transform.getRotation().getBack(); }

    inline Transform * getTransform(void){
        return &transform;
    }
    inline Matrix4f getViewMatrix(void) {
        return Matrix4f::initTranslation(transform.getPosition().getInverted()) * transform.getRotation().toRotationMatrix();
    }

    inline Vector3f& getPosition(void){
        return transform.getPosition();
    }
    inline void cleanUp(void){
        CHECK_AND_DEL(picker);
    }
//    inline const Vector3f& getMouseDirection(void) const{
//        if(IS_NULL(picker)){
//            throw getMessage(Messages::UNINITIALIZED_MOUSE_PICKER);
//        }
//        return picker -> getCurrentRay();
//    }
};

#endif //GRAPHICSPROJECT_BASICCAMERA_H
