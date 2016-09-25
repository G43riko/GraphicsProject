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
        bool mouseLocked = false;
        Vector2f lastMousePos;
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

        Vector3f * getForwardVector(void);
        Vector3f * getRightVector(void);
        Vector3f * getUpVector(void);
};

#include "../utils/Maths.h"
#endif //GRAPHICSPROJECT_CAMERA_H
