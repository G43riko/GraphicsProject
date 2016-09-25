//
// Created by gabriel on 25.9.2016.
//

#ifndef GRAPHICSPROJECT_CAMERA_H
#define GRAPHICSPROJECT_CAMERA_H

#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "WindowManager.h"
#include "../utils/Input.h"
#include "../utils/Vectors.h"
#include <math.h>

class Camera {
    private:
        static Vector3f * UP;
        glm::mat4 projectionMatrix;
        bool VERTICAL = true;
        const float FOV = 70.0f;
        const float NEAR_PLANE = 0.1f;
        const float FAR_PLANE = 1000.0f;
        Vector3f * forward = new Vector3f(0, 0, 1);
    public:
        Vector3f * position = new Vector3f(0, 0, 0);
        float pitch = 0;
        float yaw = 0;
        float roll = 0;
        Camera(void);
        glm::mat4 getProjectionMatrix(void);
        void input(void);
        glm::mat4 getViewMatrix(void);
        void updateForward(void);

        Vector3f * getForwardVector(){
            if(VERTICAL)
                return forward -> getMul(-1) -> normalize();

            return UP -> getCross(forward) -> cross(UP) -> mul(-1) -> normalize();
        }

        Vector3f * getRightVector(){
            return UP -> getCross(forward) -> normalize();
        }

        Vector3f * getUpVector(){
            return UP -> getNormal();
        }
};

#endif //GRAPHICSPROJECT_CAMERA_H
