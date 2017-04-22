//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_CAMERA_H
#define GRAPHICSPROJECT_CAMERA_H

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../utils/Input.h"
#include "../rendering/WindowManager.h"
#include <sys/time.h>
#include "../utils/Vectors.h"
#include <math.h>
#include <src/utils/Transform.h>
#include <src/utils/MousePicker.h>


class MousePicker;
class Camera {
    private:
    glm::mat4 projectionMatrix;
        Transform transform     = Transform();
        bool VERTICAL           = true;
        MousePicker * picker    = nullptr;
        Vector3f forward        = Vector3f(1, 0, 0);
//    Vector3f position   = Vector3f(DEFAULT_CAMERA_POSITION);//TODO deprecated
    public:
        Vector3f getForward(void);
//        void updateForward(){
//            forward.x = (float)(sin((-yaw + 180)) * cos(-pitch));
//            forward.y = (float)sin((-pitch + 180));
//            forward.z = (float)(cos((-yaw)) * cos(-pitch));
//            forward.normalize();
//        }
        Vector3f getPosition(void)&{
            return * transform.getPosition();
        }
//        void setPosition(Vector3f pos){
//            position = pos;
//        }
        float FOV           = DEFAULT_CAMERA_FOV;
        float FAR_PLANE     = DEFAULT_CAMERA_FAR_PLANE;
        float NEAR_PLANE    = DEFAULT_CAMERA_NEAR_PLANE;
        float pitch         = 0;
        float roll          = 0;
        float yaw           = 0;

        Transform * getTransform(void){
            return &transform;
        }
        Camera(void);
        glm::mat4 getProjectionMatrix(void);
        glm::mat4 getViewMatrix(void);
        void cleanUp(void);
        void show(){
            printf("pitch: %f, yaw: %f, roll: %f\n", pitch, yaw, roll);
        }
        Vector3f getForwardVector(){
            forward = transform.getRotation()->getForward();
            if(VERTICAL){
                return (forward * -1).getNormal();
            }
            return (Vector3f(0, 1, 0).cross(&forward).getCross(Vector3f(0, 1, 0)) * -1).normalize();
        }
        Vector3f getRightVector(){
            forward = transform.getRotation()->getForward();
            return Vector3f(0, 1, 0).cross(&forward).normalize();
        }
};

typedef std::shared_ptr<Camera> PointerCamera;

#include "../utils/Maths.h"
#endif //GRAPHICSPROJECT_CAMERA_H
