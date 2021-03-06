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


//class MousePicker;

class Camera : public BasicCamera{
    const bool VERTICAL  = false;
public:
    float pitch         = 0;
    float roll          = 0;
    float yaw           = 0;

    inline Camera(void){
        //projectionMatrix = Matrix4f::initPerspective(FOV, WindowManager::getRation(), NEAR_PLANE, FAR_PLANE); //TODO toto nefunguje
        projectionMatrix = Matrix4f(glm::perspectiveFov<float>(FOV,
                                                               static_cast<float>(WindowManager::width),
                                                               static_cast<float>(WindowManager::height),
                                                               NEAR_PLANE,
                                                               FAR_PLANE));
        //picker = new MousePicker(this);
    }
    inline void cleanUp(void){
        //delete picker;
    }

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
