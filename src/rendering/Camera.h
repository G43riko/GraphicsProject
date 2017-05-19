//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_CAMERA_H
#define GRAPHICSPROJECT_CAMERA_H

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../rendering/WindowManager.h"
#include <sys/time.h>
#include "src/utils/math/objects/Vectors.h"
#include <math.h>
#include <src/core/BasicCamera.h>


class MousePicker;
class Camera : public BasicCamera{
private:
    const bool VERTICAL           = false;
//    Vector3f forward        = Vector3f(1, 0, 0);
//    Vector3f position   = Vector3f(DEFAULT_CAMERA_POSITION);//TODO deprecated
public:
//        void updateForward(){
//            forward.x = (float)(sin((-yaw + 180)) * cos(-pitch));
//            forward.y = (float)sin((-pitch + 180));
//            forward.z = (float)(cos((-yaw)) * cos(-pitch));
//            forward.normalize();
//        }
//        void setPosition(Vector3f pos){
//            position = pos;
//        }
    const float FOV           = DEFAULT_CAMERA_FOV;
    const float FAR_PLANE     = DEFAULT_CAMERA_FAR_PLANE;
    const float NEAR_PLANE    = DEFAULT_CAMERA_NEAR_PLANE;
    float pitch         = 0;
    float roll          = 0;
    float yaw           = 0;

    Transform * getTransform(void){
        return &transform;
    }
    inline Camera(void){
        projectionMatrix = glm::perspectiveFov<float>(FOV,
                                                      static_cast<float>(WindowManager::width),
                                                      static_cast<float>(WindowManager::height),
                                                      NEAR_PLANE,
                                                      FAR_PLANE);
        //picker = new MousePicker(this);
    }
    inline void cleanUp(void){
        //delete picker;
    }
//    inline void show(void) const{
//        printf("pitch: %f, yaw: %f, roll: %f\n", pitch, yaw, roll);
//    }

    //GETTERS
    inline Vector3f getForwardVector(void){
        const Vector3f forward = transform.getRotation().getForward();
        if(VERTICAL){
            return (forward * -1).getNormal();
        }
        return (Vector3f(0, 1, 0).cross(forward).getCross(Vector3f(0, 1, 0)) * -1).normalize();
    }
    inline Vector3f getRightVector(void){
        const Vector3f forward = transform.getRotation().getForward();
        return Vector3f(0, 1, 0).cross(forward).normalize();
    }
};


#include "src/utils/math/Maths.h"
#endif //GRAPHICSPROJECT_CAMERA_H
